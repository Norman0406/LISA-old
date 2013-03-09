/***********************************************************************
*
* LISA: Lightweight Integrated System for Amateur Radio
* Copyright (C) 2013 Norman Link <norman.link@gmx.net>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
***********************************************************************/

#include "AudioSpectrumWorker.h"
#include "AudioSpectrum.h"
#include "AudioDevice.h"
#include <QtCore/qmath.h>
#include <QtCore/qnumeric.h>

#include <QtCore/QDebug>
#include <QtCore/QThread>

namespace digital
{
    AudioSpectrumWorker::AudioSpectrumWorker(int fftSize, AudioSpectrumWindow windowFunc)
        : m_fftIn(0), m_fftOut(0), m_fftPlan(0), m_window(0), m_terminate(false),
        m_windowAvg(0), m_dcComp(0), m_nyquistFrq(0)
    {
        // UNDONE: check
        // fftSize has to be a multiple of 2
        /*const int exp = qLn(fftSize) / M_LN2;// fftSize % 2;
        if (mod % 2 != 0) {
            qWarning() << "invalid fft size: " << fftSize;
            fftSize = 0;
        }*/
            //throw "Invalid FFT size"; 
        
        m_fftSize = fftSize;
        m_specSize = (m_fftSize / 2) + 1;

        m_windowFunc = windowFunc;
        m_spectrum.resize(m_specSize);
        m_spectrumMagSq.resize(m_specSize);
        m_spectrumLog.resize(m_specSize);

        m_passMin = 0;
        m_passMax = 4000;
        
        qDebug() << "using FFT size: " << m_fftSize;
    }

    AudioSpectrumWorker::~AudioSpectrumWorker()
    {
        stop();
    }
    
    void AudioSpectrumWorker::stop()
    {
        m_mutexIn.lock();
        m_terminate = true;
        m_dataReady.wakeAll();
        m_mutexIn.unlock();
    }

    void AudioSpectrumWorker::startFFT(const QAudioFormat& format, const QByteArray& buffer)
    {
        // set data
        m_mutexIn.lock();
        m_bufferIn = buffer;
        m_format = format;
        m_mutexIn.unlock();

        if (!m_format.isValid()) {
            qCritical() << "format is invalid";
            throw "format is invalid";
        }

        // wake thread to process next FFT
        m_dataReady.wakeAll();
    }
    
    void AudioSpectrumWorker::run()
    {
        // create a plan for real 2 complex fft
        m_fftIn = (double*)fftw_malloc(sizeof(double) * m_fftSize);
        m_fftOut = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * m_specSize);
        m_fftPlan = fftw_plan_dft_r2c_1d(m_fftSize, m_fftIn, m_fftOut, FFTW_ESTIMATE); // or FFTW_ESTIMATE ?

        // create the window function
        m_window = new double[m_fftSize];
        createWindow();

        m_terminate = false;

        while (!m_terminate) {
            // wait for incoming data to process
            m_mutexIn.lock();
            while (m_bufferIn.isEmpty() && !m_terminate)
                m_dataReady.wait(&m_mutexIn);
            m_mutexIn.unlock();

            if (!m_terminate) {
                // compute fft on the data
                compute(m_format, m_bufferIn);
                
                // convert passband from frequency scale to fft bin scale
                const double binScale = m_specSize / (m_format.sampleRate() / 2.0);
                const int minBin = (int)(m_passMin * binScale);
                const int maxBin = (int)(m_passMax * binScale);
                const int binRange = maxBin - minBin;

                // lock to save output data
                m_mutexOut.lock();
                m_isOutputReady = false;

                // resize output vectors if passband changed
                if (m_spectrum.size() != binRange)
                    m_spectrum.resize(binRange);
                if (m_spectrumMagSq.size() != binRange)
                    m_spectrumMagSq.resize(binRange);
                if (m_spectrumLog.size() != binRange)
                    m_spectrumLog.resize(binRange);
                if (m_spectrumPhase.size() != binRange)
                    m_spectrumPhase.resize(binRange);

                // get interesting data
                m_dcComp = m_fftOut[0][0];
                m_nyquistFrq = m_fftOut[m_specSize - 1][0];
                
                //const double norm = 1.0 / m_fftSize;
                //const double minDb = -130;
                //const double maxDb = 0;
                //const double maxDbOffset = maxDb / 10.0;
                //const double dbGainOffset = -10.0 / (maxDb - minDb);

                const double minDb = qAbs(20 * getLog10(1 / 65536.0f));

                // get normalization factors
                double avg = 0;
                for (int i = 0; i < m_specSize; i++) {
                    std::complex<double> value(m_fftOut[i][0], m_fftOut[i][1]);
                    //value /= m_windowAvg * m_specSize;
                    double mag = getMagnitude(value);
                    avg += mag;
                }
                avg /= m_specSize;

                // get spectrum
                for (int i = 0; i < m_specSize; i++) {
                    std::complex<double> value(m_fftOut[i][0], m_fftOut[i][1]);
                    value /= m_windowAvg * m_specSize * avg;
                    
                    double mag = getMagnitude(value);
                    //mag /= (m_windowAvg * m_specSize);
                    //mag /= avg;

                    double log = 20 * getLog10(mag);

                    log += minDb;	// add up the dynamic range from audio samples
                    log /= minDb;	// convert to [-inf, 1]

                    if (log < 0)	// clamp -inf
                        log = 0;
                                        
                    double phase = qAtan2(value.imag(), value.real());
                    
                    // save spectrum inside passband
                    if (i >= minBin && i < maxBin) {
                        int passIndex = i - minBin;

                        if (m_spectrum.size() != maxBin - minBin) {
                            qCritical() << "spectrum size is invalid";
                            throw "spectrum size is invalid";
                        }

                        m_spectrum[passIndex] = value;
                        m_spectrumMagSq[passIndex] = mag;
                        m_spectrumLog[passIndex] = log;
                        m_spectrumPhase[passIndex] = phase;
                    }
                }
                m_isOutputReady = true;
                m_mutexOut.unlock();
                m_outputReady.wakeAll();
                
                // signal that data is ready
                emit dataReady();
            }
        }
        
        // free memory
        delete[] m_window;
        m_window = 0;
        
        m_bufferIn.clear();

        fftw_destroy_plan(m_fftPlan);
        fftw_free(m_fftIn);
        fftw_free(m_fftOut);

        m_fftPlan = 0;
        m_fftIn = 0;
        m_fftOut = 0;

        // signal that thread is finished
        emit finished();
    }

    void AudioSpectrumWorker::compute(const QAudioFormat& format, const QByteArray& buffer)
    {
        m_mutexIn.lock();

        const int bytesPerSample = format.sampleSize() * format.channelCount() / 8;
        
        // Initialize data array
        const char* ptr = buffer.constData();
        for (int i = 0; i < m_fftSize; i++) {
            const qint16 sample = *reinterpret_cast<const qint16*>(ptr);
            
            if (i < m_fftSize / 1) {
                // create fft sample
                double pcmSample = AudioDevice::pcmToReal(sample);
                pcmSample *= m_window[i];
                m_fftIn[i] = pcmSample;
            }
            else
                m_fftIn[i] = 0;

            ptr += bytesPerSample;
        }

        m_bufferIn.clear();	// necessary?

        m_mutexIn.unlock();

        // perform fourier transform
        fftw_execute(m_fftPlan);
    }

    int AudioSpectrumWorker::getFFTSize() const
    {
        return m_fftSize;
    }
    
    int AudioSpectrumWorker::getSpectrumSize() const
    {
        return m_spectrum.size();
    }

    const QVector<std::complex<double> >& AudioSpectrumWorker::getSpectrum()
    {
        // wait until data is ready
        m_mutexOut.lock();
        while (!m_isOutputReady)
            m_outputReady.wait(&m_mutexOut);
        m_mutexOut.unlock();

        return m_spectrum;
    }

    const QVector<double>& AudioSpectrumWorker::getSpectrumMagSq()
    {
        // wait until data is ready
        m_mutexOut.lock();
        while (!m_isOutputReady)
            m_outputReady.wait(&m_mutexOut);
        m_mutexOut.unlock();

        return m_spectrumMagSq;
    }

    const QVector<double>& AudioSpectrumWorker::getSpectrumLog()
    {
        // wait until data is ready
        m_mutexOut.lock();
        while (!m_isOutputReady)
            m_outputReady.wait(&m_mutexOut);
        m_mutexOut.unlock();

        return m_spectrumLog;
    }
    
    void AudioSpectrumWorker::setPassband(int min, int max)
    {
        if (min < 0) {
            qWarning() << "minimum passband out of range: " << min;
            min = 0;
        }

        if (min > max) {
            qWarning() << "minimum passband above maximum passband: " << min << ", " << max;
            min = max - 1;
        }

        m_passMin = min;
        m_passMax = max;
    }
    
    void AudioSpectrumWorker::getPassband(int& min, int& max) const
    {
        min = m_passMin;
        max = m_passMax;
    }

    void AudioSpectrumWorker::createWindow()
    {
        double pwr = 0;
        for (int i = 0; i < m_fftSize; i++) {
            m_window[i] = calcWindowFunc(i);
            pwr += m_window[i] * m_window[i];
        }
        
        m_windowAvg = 0;
        pwr = qSqrt((double)m_fftSize / pwr);
        for (int i = 0; i < m_fftSize; i++) {
            m_window[i] *= pwr;
            m_windowAvg += m_window[i];
        }
        m_windowAvg /= m_fftSize;
    }
    
    double AudioSpectrumWorker::calcWindowFunc(const int sample)
    {
        const double val = sample / (double)m_fftSize;

        switch (m_windowFunc) {
        case WT_RECT:
            return 1.0;
        case WT_HANNING:
            return 0.5 - 0.5 * qCos(2 * M_PI * val);
        case WT_HAMMING:
            return 0.54 - 0.46 * cos(2 * M_PI * val);
        case WT_BLACKMAN:
            return 0.42 - 0.50 * qCos(2 * M_PI * val) + 0.08 * qCos(4 * M_PI * val);
        case WT_BLACKMANHARRIS:
            return 0.35875 - 0.48829 * qCos(2 * M_PI * val) + 0.14128 * qCos(4 * M_PI * val) - 0.01168 * qCos(6 * M_PI * val);
        default:
            return 0;
        }
    }
    
    double AudioSpectrumWorker::getMagnitude(const std::complex<double>& fftVal) const
    {
        return qSqrt(getMagnitudeSqr(fftVal));
    }

    double AudioSpectrumWorker::getMagnitudeSqr(const std::complex<double>& fftVal) const
    {
        return fftVal.real() * fftVal.real() + fftVal.imag() * fftVal.imag();
    }
    
    double AudioSpectrumWorker::getLog10(const double val) const
    {
        if (val == 0)
            return 0;

        return qLn(val) / M_LN10;
    }
}

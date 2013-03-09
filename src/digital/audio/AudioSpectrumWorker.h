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

#ifndef DIGITAL_AUDIOSPECTRUMWORKER_H
#define DIGITAL_AUDIOSPECTRUMWORKER_H

#include <QtCore/QObject>
#include <fftw/fftw3.h>
#include <QtMultimedia/QAudioFormat>
#include <QtCore/QVector>
#include <QtCore/QMutex>
#include <QtCore/QWaitCondition>
#include <complex>
#include "AudioSpectrum.h"

namespace digital
{
    // threading method (not subclassing QThread) discussed in
    // http://mayaposch.wordpress.com/2011/11/01/how-to-really-truly-use-qthreads-the-full-explanation/
    // http://blog.qt.digia.com/blog/2010/06/17/youre-doing-it-wrong/
    class AudioSpectrumWorker
        : public QObject
    {
        Q_OBJECT

    public:
        AudioSpectrumWorker(int, AudioSpectrumWindow);
        ~AudioSpectrumWorker();

        void stop();

        int getFFTSize() const;
        int getSpectrumSize() const;
        const QVector<std::complex<double> >& getSpectrum();
        const QVector<double>& getSpectrumMagSq();
        const QVector<double>& getSpectrumLog();

    public slots:
        void startFFT(const QAudioFormat&, const QByteArray&);
        void setPassband(int min, int max);
        void getPassband(int& min, int& max) const;
        void run();

    signals:
        void dataReady();
        void finished();

    private:
        void createWindow();
        double calcWindowFunc(const int);
        void compute(const QAudioFormat&, const QByteArray&);
        double getMagnitude(const std::complex<double>&) const;
        double getMagnitudeSqr(const std::complex<double>&) const;
        double getLog10(const double) const;

        double* m_fftIn;
        fftw_complex* m_fftOut;
        fftw_plan m_fftPlan;
        int m_fftSize;
        int m_specSize;
        AudioSpectrumWindow m_windowFunc;
        double* m_window;
        bool m_terminate;
        double m_windowAvg;

        QMutex m_mutexIn;
        QWaitCondition m_dataReady;
        
        QMutex m_mutexOut;
        QWaitCondition m_outputReady;
        bool m_isOutputReady;

        QByteArray m_bufferIn;
        QAudioFormat m_format;

        QVector<std::complex<double> > m_spectrum;	// complex spectrum
        QVector<double> m_spectrumMagSq;	// squared magnitude spectrum
        QVector<double> m_spectrumLog;		// logarithmic spectrum
        QVector<double> m_spectrumPhase;	// spectrum's phase

        int m_passMin;	// passband min frq in [Hz]
        int m_passMax;	// passband max frq in [Hz]
        
        double m_dcComp;		// dc component
        double m_nyquistFrq;	// nyquist frequency
    };
}

#endif // DIGITAL_AUDIOSPECTRUM_H

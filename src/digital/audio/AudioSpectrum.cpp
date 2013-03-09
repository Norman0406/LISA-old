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

#include "AudioSpectrum.h"
#include "AudioSpectrumWorker.h"
#include "AudioDevice.h"
#include <QtCore/qmath.h>
#include <QtCore/qnumeric.h>
#include <QtCore/QThread>
#include <QtCore/QDebug>

namespace digital
{
    AudioSpectrum::AudioSpectrum(int fftSize, AudioSpectrumWindow wdType, QObject* parent)
        : QObject(parent), m_fftWorker(0), m_fftThread(0)
    {
        m_fftThread = new QThread(this);
        m_fftWorker = new AudioSpectrumWorker(fftSize, wdType);
        m_fftWorker->moveToThread(m_fftThread);
        
        connect(m_fftThread, &QThread::started, m_fftWorker, &AudioSpectrumWorker::run);
        connect(m_fftWorker, &AudioSpectrumWorker::finished, m_fftThread, &QThread::quit);
        connect(m_fftWorker, &AudioSpectrumWorker::finished, m_fftWorker, &AudioSpectrumWorker::deleteLater);
        connect(m_fftThread, &QThread::finished, m_fftThread, &QThread::deleteLater);
        connect(m_fftWorker, &AudioSpectrumWorker::dataReady, this, &AudioSpectrum::spectrumReady);
    }

    AudioSpectrum::~AudioSpectrum()
    {
        m_fftWorker->stop();
        m_fftThread->quit();	// wouldn't be necessary if finished would be called properly
        m_fftThread->wait();
    }
    
    void AudioSpectrum::init()
    {
        // get default passband
        int passMin, passMax;
        getPassband(passMin, passMax);
        emit passbandChanged(passMin, passMax);

        // start thread
        if (m_fftThread)
            m_fftThread->start();
    }

    void AudioSpectrum::compute(const QAudioFormat& format, const QByteArray& buffer)
    {
        // start processing FFT
        if (m_fftWorker)
            m_fftWorker->startFFT(format, buffer);
    }
    
    void AudioSpectrum::spectrumReady()
    {
        const QVector<double>& spectrumMagSq = m_fftWorker->getSpectrumMagSq();
        const QVector<double>& spectrumLog = m_fftWorker->getSpectrumLog();
        m_spectrumVis = spectrumLog;
        
        for (int i = 0; i < m_spectrumVis.size(); i++)
            m_spectrumVis[i] = spectrumLog[i] * 255;

        int passMin, passMax;
        getPassband(passMin, passMax);

        emit dataReady(m_spectrumVis, passMin, passMax);
    }

    int AudioSpectrum::getFFTSize() const
    {
        return m_fftWorker ? m_fftWorker->getFFTSize() : 0;
    }
    
    int AudioSpectrum::getSpectrumSize() const
    {
        return m_fftWorker ? m_fftWorker->getSpectrumSize() : 0;
    }
    
    void AudioSpectrum::setPassband(int min, int max)
    {
        if (m_fftWorker) {
            m_fftWorker->setPassband(min, max);
            emit passbandChanged(min, max);
        }
    }

    void AudioSpectrum::getPassband(int& min, int& max) const
    {
        if (m_fftWorker)
            m_fftWorker->getPassband(min, max);
    }
}

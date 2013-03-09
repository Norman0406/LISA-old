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

#ifndef DIGITAL_AUDIOSPECTRUM_H
#define DIGITAL_AUDIOSPECTRUM_H

#include <QtCore/QObject>
#include <QtMultimedia/QAudioFormat>
#include <QtCore/QVector>
#include <complex>

namespace digital
{	
    enum AudioSpectrumWindow {
        WT_RECT = 0,
        WT_HANNING,	// or HANN?
        WT_HAMMING,
        WT_BLACKMAN,
        WT_BLACKMANHARRIS,
    };

    class AudioSpectrumWorker;

    class AudioSpectrum
        : public QObject
    {
        Q_OBJECT

    public:
        // UNDONE: add blackman and blackman-harris
        // see here: http://en.wikipedia.org/wiki/Window_function#Hamming_window

        AudioSpectrum(int, AudioSpectrumWindow, QObject*);
        ~AudioSpectrum();
        
        void init();
        int getFFTSize() const;
        int getSpectrumSize() const;
        void setPassband(int min, int max);
        void getPassband(int& min, int& max) const;

    public slots:
        void compute(const QAudioFormat& format, const QByteArray& buffer);
        void spectrumReady();

    signals:
        void dataReady(const QVector<double>&, int, int);
        void passbandChanged(int min, int max);

    private:		
        QVector<double> m_spectrumVis;
        AudioSpectrumWorker* m_fftWorker;
        QThread* m_fftThread;
    };
}

#endif // DIGITAL_AUDIOSPECTRUM_H
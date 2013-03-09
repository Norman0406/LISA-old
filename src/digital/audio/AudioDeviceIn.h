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

#ifndef DIGITAL_AUDIODEVICEIN_H
#define DIGITAL_AUDIODEVICEIN_H

#include "AudioDevice.h"
#include <QtMultimedia/QAudioRecorder>

namespace digital
{	
    class AudioDeviceIn
        : public AudioDevice
    {
        Q_OBJECT

    public:
        AudioDeviceIn(QObject*);
        ~AudioDeviceIn();

        void start();
        void stop();

        const QByteArray& getBuffer(int);

    public slots:
        void notified();
        void stateChanged(QAudio::State);

    signals:
        void dataReady(const QAudioFormat&, const QByteArray& buffer);

    protected:
        void iInit(const QAudioDeviceInfo&);

    private:
        QAudioInput*	m_audioInput;
        QIODevice*		m_device;
        QByteArray		m_buffer;
    };
}

#endif // DIGITAL_AUDIODEVICEIN_H
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

#ifndef DIGITAL_AUDIODEVICE_H
#define DIGITAL_AUDIODEVICE_H

#include <QtMultimedia/QAudioInput>
#include "AudioBuffer.h"

namespace digital
{	
    // TODO: run inside a thread

    class AudioDevice
        : public QObject
    {
        Q_OBJECT

    public:
        virtual ~AudioDevice();

        void init();

        virtual void start() = 0;
        virtual void stop() = 0;

        static qreal pcmToReal(qint16 pcm);
        static qint16 realToPcm(qreal real);
        static qint64 audioLength(const QAudioFormat& format, qint64 microSeconds);

        const QAudioFormat& getFormat() const;
        
    signals:
        void dataReady(const QAudioFormat&, QByteArray& buffer, int dataLength);

    protected:
        AudioDevice(QObject*);

        virtual void iInit(const QAudioDeviceInfo&) = 0;

    //private:
        QAudioFormat		m_format;
        QIODevice*			m_device;
        QByteArray*         m_buffer;
        qint64              m_bufferSize;
        AudioBuffer*		m_audioBuffer;
    };
}

#endif // DIGITAL_AUDIODEVICE_H

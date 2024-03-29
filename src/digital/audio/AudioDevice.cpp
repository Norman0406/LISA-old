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

#include "AudioDevice.h"
#include <QtCore/QtDebug>
#include <QtMultimedia/QAudioDeviceInfo>
#include <QtMultimedia/QAudioInput>
#include <QtCore/qendian.h>

namespace digital
{
    AudioDevice::AudioDevice(QObject* parent)
        : QObject(parent), m_device(0), m_bufferSize(0)
    {
    }

    AudioDevice::~AudioDevice()
    {
        delete m_buffer;
    }
    
    void AudioDevice::init()
    {
        // create the format
        m_format.setSampleRate(8000);	// frequency
        m_format.setSampleSize(16);	// bits
        m_format.setSampleType(QAudioFormat::SignedInt);
        m_format.setChannelCount(1);
        m_format.setByteOrder(QAudioFormat::LittleEndian);
        m_format.setCodec("audio/pcm");

        // choose audio device
        QAudioDeviceInfo info(QAudioDeviceInfo::defaultInputDevice());
        if (!info.isFormatSupported(m_format)) {
            qWarning() << "format not supported, choosing default";
            m_format = info.nearestFormat(m_format);
        }

        // set buffer size
        const qint64 bufferDurationUs = 1 * 1000000;	// 5 seconds
        m_bufferSize = audioLength(m_format, bufferDurationUs);

        m_buffer = new QByteArray(m_bufferSize, 0);
        m_buffer->fill(0);

        m_audioBuffer = new AudioBuffer(m_bufferSize, this);

        iInit(info);
    }
    
    const QAudioFormat& AudioDevice::getFormat() const
    {
        return m_format;
    }

    qreal AudioDevice::pcmToReal(qint16 pcm)
    {
        // UNDONE: not inside function, determine by format type
        const quint16 PCMS16MaxAmplitude = 32768; // because minimum is -32768
        return qreal(pcm) / PCMS16MaxAmplitude;
    }

    qint16 AudioDevice::realToPcm(qreal real)
    {
        // UNDONE: not inside function, determine by format type
        const qint16  PCMS16MaxValue =  32767;
        return real * PCMS16MaxValue;
    }

    qint64 AudioDevice::audioLength(const QAudioFormat& format, qint64 microSeconds)
    {
       qint64 result = (format.sampleRate() * format.channelCount() * (format.sampleSize() / 8))
           * microSeconds / 1000000;
       result -= result % (format.channelCount() * format.sampleSize());
       return result;
    }
}

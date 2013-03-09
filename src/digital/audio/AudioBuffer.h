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

#ifndef DIGITAL_AUDIOBUFFER_H
#define DIGITAL_AUDIOBUFFER_H

#include <QtCore/QIODevice>

namespace digital
{
    class AudioBuffer
        : public QIODevice
    {
        Q_OBJECT

    public:
        AudioBuffer(qint64, QObject*);
        ~AudioBuffer();

        qint64 writeData(const char*, qint64);
        qint64 readData(char*, qint64);
        
        qint64 getSampleBuffer(QByteArray&, qint64) const;
        qint64 getSampleBuffer(char*, qint64) const;
        
    private:
        char* m_buffer;
        qint64 m_bufferSize;
        qint64 m_bufferLength;
        qint64 m_position;
    };
}

#endif // DIGITAL_AUDIOBUFFER_H
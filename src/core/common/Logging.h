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

#ifndef CORE_LOGGING_H
#define CORE_LOGGING_H

#include <QtCore/QtMessageHandler>
#include <QtCore/QVector>
#include <QtGui/QColor>

namespace core
{
    struct LoggingEntry
    {
        QString m_line;
        QColor m_textCol;
        QtMsgType m_type;
    };

    class Logging
        : public QObject
    {
        Q_OBJECT

    public:
        virtual ~Logging();

        static Logging* instance();
        const QVector<LoggingEntry>& getEntries() const;
        static void messageHandler(QtMsgType, const QMessageLogContext&, const QString&);

    signals:
        void newLoggingEntry(const LoggingEntry&);
        
    protected:
        Logging();

    private:
        void log(QtMsgType, const QMessageLogContext&, const QString&);

        static Logging* m_instance;
        QVector<LoggingEntry> m_loggingEntries;
    };
}

#endif // CORE_LOGGING_H

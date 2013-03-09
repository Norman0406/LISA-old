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

#include "Logging.h"
#include <QtCore/qlogging.h>
#include <QtCore/QDebug>
#include <QtCore/QDateTime>

namespace core
{
    Logging* Logging::m_instance = 0;

    Logging::Logging()
    {
        qRegisterMetaType<LoggingEntry>("LoggingEntry");
        qInstallMessageHandler(Logging::messageHandler);
    }

    Logging::~Logging()
    {
        qDebug() << "Log closed at " << QDateTime::currentDateTime().toString();
        qInstallMessageHandler(0);
    }

    Logging* Logging::instance()
    {
        if (!m_instance) {
            m_instance = new Logging();
            qDebug() << "Log started at " << qPrintable(QDateTime::currentDateTime().toString());
        }

        return Logging::m_instance;
    }

    void Logging::log(QtMsgType type, const QMessageLogContext& context, const QString& msg)
    {
        QString line;
        QColor col = Qt::black;
        
        bool verbose = true;

        QString typeStr;
        switch (type) {
        case QtDebugMsg:
            typeStr = "Info";	// let's call it "Info"
            verbose = false;
            col = Qt::black;
            break;
        case QtWarningMsg:
            typeStr = "Warning";
            col = Qt::darkYellow;
            break;
        case QtCriticalMsg:	// == QtSystemMsg
            typeStr = "Critical";
            col = Qt::darkRed;
            break;
        case QtFatalMsg:
            typeStr = "Fatal";
            col = Qt::darkRed;
            break;
        default:
            typeStr = "Unknown";
            col = Qt::black;
            break;
        }

        // get detailed information
        QString file = context.file;
        QString func = context.function;
        int lineNr = context.line;
        QString verboseInfo = "\"" + file + "\"" + " : " + func + " : " + QString::number(lineNr);
        
        // construct header
        QString now = QDateTime::currentDateTime().toString("hh:mm:ss");
        QString front = "[" + now + " (" + typeStr + ")] ";
        
        line = front + msg;

        if (verbose)
            line += " (" + verboseInfo + ")";

        // remove double whitespaces
        line = line.simplified();
                        
        LoggingEntry entry;
        entry.m_type = type;
        entry.m_line = line;
        entry.m_textCol = col;

        m_loggingEntries.push_back(entry);

        // output to debugging window (visual studio specific)
#ifdef _MSC_VER
        QString dbgLine = line + "\n";
        OutputDebugString(dbgLine.toStdWString().c_str());
#endif
        
        emit newLoggingEntry(entry);
    }
    
    const QVector<LoggingEntry>& Logging::getEntries() const
    {
        return m_loggingEntries;
    }
    
    void Logging::messageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg)
    {
        Logging::instance()->log(type, context, msg);
    }
}

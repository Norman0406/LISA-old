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

#include "Exception.h"
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QApplication>
#include <QtCore/QDebug>

namespace core
{
    Exception::Exception(QString module, QString funcInfo, QString message)
        : m_module(module), m_funcInfo(funcInfo), m_message(message)
    {
    }

    Exception::~Exception() throw()
    {
    }

    const char* Exception::what() const throw()
    {
        return m_message.toStdString().c_str();
    }

    void Exception::show()
    {
        QString msg = "Module: " + m_module + "\nFunction: " + m_funcInfo + "\n\nMessage: \"" +
            m_message + "\"";

        qCritical() << m_message;

        QMessageBox::critical(0, "Exception", msg, QMessageBox::Ok);
    }
}

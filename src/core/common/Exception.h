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

#ifndef CORE_EXCEPTION_H
#define CORE_EXCEPTION_H

#include <exception>
#include <QtCore/QString>

namespace core
{
    // exception macro
#define EXCEPTION(ExClass, msg) ExClass(this->getModuleName(), Q_FUNC_INFO, msg)

    class Exception
        : public std::exception
    {
    public:
        Exception(QString module, QString funcInfo, QString message);
        virtual ~Exception() throw();

        const char* what() const throw();
        void show();

    private:
        QString m_module;
        QString m_funcInfo;
        QString m_message;
    };

    /*class SystemException;
    class ModuleException;
    class XMLException;
    class QtException;*/
}

#endif // CORE_EXCEPTION_H

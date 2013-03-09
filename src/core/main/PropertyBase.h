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

#ifndef CORE_PROPERTYBASE_H
#define CORE_PROPERTYBASE_H

#include <QtCore/QString>
#include <QtCore/QXmlStreamReader>
#include <QtCore/QXmlStreamWriter>

namespace core
{
    class PropertyBase
    {
    public:
        virtual ~PropertyBase();

        QString getNameStr() const;
        virtual QString getTypeStr() const = 0;
        virtual QString getValueStr() const = 0;
        virtual QString getDefaultValueStr() const = 0;
        virtual bool setValueFromStr(QString) = 0;
        virtual void setToDefault() = 0;
        
    protected:
        PropertyBase(const PropertyBase&);
        PropertyBase(QString);

    private:
        QString m_name;
    };
}

#endif // CORE_PROPERTYBASE_H
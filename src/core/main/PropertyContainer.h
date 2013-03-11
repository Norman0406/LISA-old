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

#ifndef CORE_PROPERTYCONTAINER_H
#define CORE_PROPERTYCONTAINER_H

#include "PropertyList.h"

namespace core
{
    class PropertyContainer
    {
    public:
        virtual ~PropertyContainer(void);

        template <typename T>
        bool addProperty(const QString& name, const T& defaultVal);

        template <typename T>
        Property<T>* getProperty(const QString& name);
        
        bool loadProperties(const QString& moduleName);
        bool saveProperties(const QString& moduleName);

    protected:
        PropertyContainer();

        PropertyList m_properties;
    };
    
    template <typename T>
    bool PropertyContainer::addProperty(const QString& name, const T& defaultVal)
    {
        return m_properties.addProperty(Property<T>(name, defaultVal));
    }
    
    template <typename T>
    Property<T>* PropertyContainer::getProperty(const QString& name)
    {
        return m_properties.getProperty<T>(name);
    }
}

#endif // CORE_PROPERTYCONTAINER_H

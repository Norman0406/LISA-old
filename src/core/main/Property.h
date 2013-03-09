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

#ifndef CORE_PROPERTY_H
#define CORE_PROPERTY_H

#include <sstream>
#include "PropertyBase.h"
#include "PropertyTraits.h"

namespace core
{
    // TODO: implement a PropertyRef<T> which takes a reference and updates automatically

    template <typename T>
    class Property
        : public PropertyBase
    {
    public:
        Property(const Property<T>& other);
        Property(QString name, T defaultVal);
        ~Property();

        void setValue(T val);
        T getValue() const;
        T getDefaultValue() const;

        QString getTypeStr() const;
        QString getValueStr() const;
        QString getDefaultValueStr() const;
        bool setValueFromStr(QString);
        void setToDefault();
                
    private:
        QString getValueStr(T) const;

        T m_value;
        T m_defaultValue;
    };

    template <typename T>
    Property<T>::Property(const Property<T>& other)
        : PropertyBase(other)
    {
        m_value = other.getValue();
        m_defaultValue = other.getDefaultValue();
    }
    
    template <typename T>
    Property<T>::Property(QString name, T defaultVal)
        : PropertyBase(name),
        m_defaultValue(defaultVal)
    {
        setValue(m_defaultValue);
    }
    
    template <typename T>
    Property<T>::~Property()
    {
    }
    
    template <typename T>
    void Property<T>::setValue(T val)
    {
        m_value = val;
    }

    template <typename T>
    T Property<T>::getValue() const
    {
        return m_value;
    }
    
    template <typename T>
    T Property<T>::getDefaultValue() const
    {
        return m_defaultValue;
    }

    template <typename T>
    QString Property<T>::getTypeStr() const
    {
        return PropertyTraits<T>::getTypeStr();
    }
    
    template <typename T>
    QString Property<T>::getValueStr() const
    {
        return getValueStr(m_value);
    }
    
    template <typename T>
    QString Property<T>::getDefaultValueStr() const
    {
        return getValueStr(m_defaultValue);
    }
    
    template <typename T>
    QString Property<T>::getValueStr(T val) const
    {
        std::stringstream sstr;
        sstr << val;
        return QString(sstr.str().c_str());
    }
    
    template <typename T>
    bool Property<T>::setValueFromStr(QString str)
    {
        T tmp;
        std::stringstream sstr(str.toStdString());
        sstr.unsetf(std::ios::dec);
        if (sstr >> tmp)
            m_value = tmp;
        else
            return false;
        
        return true;
    }

    template <typename T>
    void Property<T>::setToDefault()
    {
        setValue(m_defaultValue);
    }
}

#endif // CORE_PROPERTY_H
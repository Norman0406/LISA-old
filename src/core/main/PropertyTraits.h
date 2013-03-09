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

#ifndef CORE_PROPERTYTRAITS_H
#define CORE_PROPERTYTRAITS_H

namespace core
{
    template <typename T>
    struct PropertyTraits
    {
    };

#define MAKE_PROPERTY_TRAIT(type) \
    template <> \
    struct PropertyTraits<type> \
    { \
        static const char* getTypeStr() { \
            return #type; \
        } \
    }; \
    
    MAKE_PROPERTY_TRAIT(char);
    MAKE_PROPERTY_TRAIT(bool);
    MAKE_PROPERTY_TRAIT(int);
    MAKE_PROPERTY_TRAIT(float);
    MAKE_PROPERTY_TRAIT(double);
    MAKE_PROPERTY_TRAIT(QString);
}

#endif // CORE_PROPERTYTRAITS_H
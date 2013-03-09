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

#ifndef CORE_FACTORY_H
#define CORE_FACTORY_H

#include <QtCore/QString>
#include <QtCore/QStringList>

// no namespace to allow generic specialization

template <typename T>
class Factory
{
public:
    Factory();	// not implemented
    ~Factory();	// not implemented
        
    // implement these functions in your specialized factory
    static QStringList getKeys();
    static T* createByKey(QString);
};

#endif // CORE_FACTORY_H
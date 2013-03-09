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

#ifndef LOGBOOK_DATABASEFACTORY_H
#define LOGBOOK_DATABASEFACTORY_H

#include <core/common/Factory.h>
#include "DatabaseXML.h"

template <>
QStringList Factory<logbook::Database>::getKeys()
{
    QStringList keys;

    // push all available types here
    keys.push_back("xml");

    return QStringList();
}

template <>
logbook::Database* Factory<logbook::Database>::createByKey(QString key)
{
    // create types by key
    if (key == "xml")
        return new logbook::DatabaseXML();

    return 0;
}

#endif // LOGBOOK_DATABASEFACTORY_H

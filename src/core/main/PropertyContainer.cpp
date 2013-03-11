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

#include "PropertyContainer.h"
#include "../common/FileUtils.h"

namespace core
{
    PropertyContainer::PropertyContainer()
    {
    }

    PropertyContainer::~PropertyContainer(void)
    {
    }
    
    bool PropertyContainer::loadProperties(const QString& moduleName)
    {
        QString folder = FileUtils::openFolder(SF_CONFIG, false);

        if (!folder.isEmpty()) {
            QString filename = folder + moduleName.toLower() + ".xml";
            
            qDebug() << "loading properties for module " << moduleName << " from " << filename;

            return m_properties.loadFromFile(filename, moduleName);
        }

        return false;
    }

    bool PropertyContainer::saveProperties(const QString& moduleName)
    {
        QString folder = FileUtils::openFolder(SF_CONFIG, true);

        if (!folder.isEmpty()) {
            QString filename = folder + moduleName.toLower() + ".xml";

            qDebug() << "saving properties for module " << moduleName << " to " << filename;

            return m_properties.saveToFile(filename, moduleName);
        }

        return false;

    }
}

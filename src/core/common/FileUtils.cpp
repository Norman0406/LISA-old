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

#include "FileUtils.h"
#include <QtGui/QGuiApplication>
#include <QtCore/QDir>

namespace core
{
    QString FileUtils::getFolderStr(SystemFolder folder)
    {
        switch (folder) {
        case SF_APPLICATION:
            return qApp->applicationDirPath();
        case SF_CONFIG:
            return qApp->applicationDirPath() + "/cfg/";
        }

        return "<invalid>";
    }
    
    QString FileUtils::openFolder(SystemFolder folder, bool create)
    {
        return openFolder(getFolderStr(folder), create);
    }

    QString FileUtils::openFolder(QString folder, bool create)
    {
        if (!QDir(folder).exists()) {
            if (create) {
                QDir().mkdir(folder);
                return folder;
            }
            else
                return QString();
        }

        return folder;
    }
}

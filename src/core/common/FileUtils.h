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

#ifndef CORE_FILEUTILS_H
#define CORE_FILEUTILS_H

#include <QtCore/QString>

namespace core
{
    enum SystemFolder
    {
        SF_APPLICATION,
        SF_CONFIG,
    };

    // pure static
    class FileUtils
    {
    public:
        static QString getFolderStr(SystemFolder);
        static QString openFolder(SystemFolder folder, bool create);
        static QString openFolder(QString folder, bool create);
    };
}

#endif // CORE_FILEUTILS_H
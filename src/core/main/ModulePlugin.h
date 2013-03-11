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

#ifndef CORE_MODULEBASE_H
#define CORE_MODULEBASE_H

#include <QtCore/QString>
#include <QtCore/QtPlugin>

namespace core
{
    class ModulePlugin
        : public QObject
    {
        Q_OBJECT

    public:
        virtual ~ModulePlugin(void) { }
        
        // module identifying functions
        virtual QString	getModuleName() const = 0;
        virtual QString getDisplayName() const = 0;
        
    protected:
        virtual bool iInit(QWidget*) = 0;
    };
}

#define ModulePlugin_iid "LISA.core.moduleplugin"
Q_DECLARE_INTERFACE(core::ModulePlugin, ModulePlugin_iid)

#endif // CORE_MODULEBASE_H

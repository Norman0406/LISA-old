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

#include "Module.h"
#include "../common/FileUtils.h"

namespace core
{
    Module::Module()
        : m_isInit(false), m_parent(0)
    {
        qRegisterMetaType<core::Module::WidgetType>("core::Module::WidgetType");
    }

    Module::~Module(void)
    {
    }
    
    bool Module::init(QWidget* parent)
    {		
        // has it already been init?
        if (m_isInit)
            return false;

        qDebug() << "initializing module: " << getModuleName();

        // load properties from file
        loadProperties(getModuleName());

        m_parent = parent;

        // init module
        if (iInit(parent))
            m_isInit = true;

        if (m_isInit)
            qDebug() << "module " << getModuleName() << " was successfully initialized";

        // was it successful?
        return m_isInit;
    }
    
    bool Module::postInitAll()
    {
        if (!isInit()) {
            qCritical() << "module not initialized before post init";
            return false;
        }

        iPostInitAll();

        if (!isInit()) {
            qCritical() << "module not initialized after post init";
            return false;
        }

        return true;
    }

    void Module::iPostInitAll()
    {
    }

    bool Module::isInit() const
    {
        return m_isInit;
    }

    void Module::getModuleWidgets(core::Module::WidgetType type, QWidget* parent, QVector<QPair<QString, QWidget*> >& widgets)
    {
        Q_UNUSED(type);
        Q_UNUSED(parent);
        Q_UNUSED(widgets);
    }

    void Module::msgReceive(QString id, const QVariant& value)
    {
        // overload this function to receive registered messages
        Q_UNUSED(id);
        Q_UNUSED(value);
    }
}

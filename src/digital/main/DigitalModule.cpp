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

#include "../gui/WdgOptions.h"
#include "DigitalModule.h"

namespace digital
{
    DigitalModule::DigitalModule()
        : Module(), m_digital(0), m_toolbar(0), m_sidebar(0)
    {
    }

    DigitalModule::~DigitalModule(void)
    {
    }
        
    QString	DigitalModule::getModuleName() const
    {
        return "Digital";
    }

    QString DigitalModule::getDisplayName() const
    {
        return "Digital Modes";
    }

    bool DigitalModule::isInit() const
    {
        return m_digital && m_toolbar && m_sidebar &&
            Module::isInit();
    }

    bool DigitalModule::iInit(QWidget* parent)
    {
        m_digital = new WdgDigital(parent);
        if (!m_digital)
            return false;

        addModuleWidget(core::Module::WT_MAIN, getDisplayName(), m_digital);

        m_toolbar = new WdgToolbar(parent);
        if (!m_toolbar)
            return false;

        addModuleWidget(core::Module::WT_TOOLBAR, getDisplayName(), m_toolbar);

        m_sidebar = new WdgSidebar(parent);
        if (!m_sidebar)
            return false;

        addModuleWidget(core::Module::WT_SIDEBAR, getDisplayName(), m_sidebar);
                
        return true;
    }
            
    void DigitalModule::createOptionWidgets(QVector<QPair<QString, core::OptionsBase*> >& widgets, QWidget* parent)
    {
        WdgOptions* wdg = new WdgOptions(&m_properties, this, parent);
        connect(this, &DigitalModule::destroyed, wdg, &WdgOptions::deleteLater);
        widgets.push_back(QPair<QString, core::OptionsBase*>(getDisplayName(), wdg));
    }

    QByteArray DigitalModule::saveGeometry()
    {
        return m_digital->saveGeometry();
    }

    bool DigitalModule::restoreGeometry(const QByteArray& geometry)
    {
        return m_digital->restoreGeometry(geometry);
    }
    
    QByteArray DigitalModule::saveState()
    {
        return m_digital->saveState();
    }

    bool DigitalModule::restoreState(const QByteArray& state)
    {
        return m_digital->restoreState(state);
    }
}

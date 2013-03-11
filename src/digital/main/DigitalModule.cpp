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
        : Module(), m_digital(0), m_toolbar(0), m_sidebar(0), m_options(0)
    {
    }

    DigitalModule::~DigitalModule(void)
    {
        if (m_digital)
            m_digital->deleteLater();
        if (m_toolbar)
            m_toolbar->deleteLater();
        if (m_sidebar)
            m_sidebar->deleteLater();
        if (m_options)
            m_options->deleteLater();
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
        
        m_toolbar = new WdgToolbar(parent);
        if (!m_toolbar)
            return false;
        
        m_sidebar = new WdgSidebar(parent);
        if (!m_sidebar)
            return false;
                        
        return true;
    }
    
    void DigitalModule::clearOptions()
    {
        m_options = 0;
    }
    
    void DigitalModule::getModuleWidgets(core::Module::WidgetType type, QWidget* parent, QVector<QPair<QString, QWidget*> >& widgets)
    {
        switch (type) {
        case core::Module::WT_MAIN:
            widgets.push_back(QPair<QString, QWidget*>(getDisplayName(), m_digital));
            break;
        case core::Module::WT_TOOLBAR:
            widgets.push_back(QPair<QString, QWidget*>(getDisplayName(), m_toolbar));
            break;
        case core::Module::WT_SIDEBAR:
            widgets.push_back(QPair<QString, QWidget*>(getDisplayName(), m_sidebar));
            break;
        case core::Module::WT_OPTIONS:
            if (!m_options) {
                m_options = new WdgOptions(&m_properties, parent);
                connect(m_options, &WdgOptions::destroyed, this, &DigitalModule::clearOptions);
            }
            widgets.push_back(QPair<QString, QWidget*>(getDisplayName(), m_options));
            break;
        }
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

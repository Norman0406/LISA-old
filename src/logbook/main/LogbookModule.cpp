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

#include "../gui/WdgLogEntry.h"
#include "LogbookModule.h"

namespace logbook
{
    LogbookModule::LogbookModule()
        : Module(), m_logbook(0), m_toolbar(0), m_sidebar(0), m_options(0)
    {
    }

    LogbookModule::~LogbookModule(void)
    {
        if (m_logbook)
            m_logbook->deleteLater();
        if (m_toolbar)
            m_toolbar->deleteLater();
        if (m_sidebar)
            m_sidebar->deleteLater();
        if (m_options)
            m_options->deleteLater();
    }
    
    QString	LogbookModule::getModuleName() const
    {
        return "Logbook";
    }

    QString LogbookModule::getDisplayName() const
    {
        return getModuleName();
    }

    bool LogbookModule::isInit() const
    {
        return m_logbook && m_toolbar && m_sidebar &&
            Module::isInit();
    }

    bool LogbookModule::iInit(QWidget* parent)
    {
        m_logbook = new WdgLogbook(parent);
        if (!m_logbook)
            return false;
        
        m_toolbar = new WdgToolbar(parent);
        if (!m_toolbar)
            return false;
        
        m_sidebar = new WdgSidebar(parent);
        if (!m_sidebar)
            return false;
                
        return true;
    }

    void LogbookModule::clearOptions()
    {
        m_options = 0;
    }
    
    void LogbookModule::getModuleWidgets(core::Module::WidgetType type, QWidget* parent, QVector<QPair<QString, QWidget*> >& widgets)
    {
        switch (type) {
        case core::Module::WT_MAIN:
            widgets.push_back(QPair<QString, QWidget*>(getDisplayName(), m_logbook));
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
                connect(m_options, &WdgOptions::destroyed, this, &LogbookModule::clearOptions);
            }
            widgets.push_back(QPair<QString, QWidget*>(getDisplayName(), m_options));
            break;
        }
    }

    QByteArray LogbookModule::saveGeometry()
    {
        return m_logbook->saveGeometry();
    }

    bool LogbookModule::restoreGeometry(const QByteArray& geometry)
    {
        return m_logbook->restoreGeometry(geometry);
    }
    
    QByteArray LogbookModule::saveState()
    {
        return m_logbook->saveState();
    }

    bool LogbookModule::restoreState(const QByteArray& state)
    {
        return m_logbook->restoreState(state);
    }
}

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
#include "../gui/WdgOptions.h"
#include "LogbookModule.h"

namespace logbook
{
    LogbookModule::LogbookModule()
        : Module(), m_logbook(0), m_toolbar(0), m_sidebar(0)
    {
    }

    LogbookModule::~LogbookModule(void)
    {
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

        addModuleWidget(core::Module::WT_MAIN, getDisplayName(), m_logbook);

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
    
    void LogbookModule::createOptionWidgets(QVector<QPair<QString, core::OptionsBase*> >& widgets, QWidget* parent)
    {
        WdgOptions* wdg = new WdgOptions(&m_properties, this, parent);
        connect(this, &LogbookModule::destroyed, wdg, &WdgOptions::deleteLater);
        widgets.push_back(QPair<QString, core::OptionsBase*>(getDisplayName(), wdg));
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

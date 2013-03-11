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

#ifndef LOGBOOK_LOGBOOKMODULE_H
#define LOGBOOK_LOGBOOKMODULE_H

#include <core/main/Module.h>
#include "../gui/WdgLogbook.h"
#include "../gui/WdgToolbar.h"
#include "../gui/WdgSidebar.h"
#include "../gui/WdgOptions.h"

namespace logbook
{
    class LogbookModule
        : public core::Module
    {
        Q_OBJECT
        Q_PLUGIN_METADATA(IID ModuleBase_iid)
        Q_INTERFACES(core::ModuleBase)

    public:
        LogbookModule();
        ~LogbookModule(void);

        QString	getModuleName() const;
        QString getDisplayName() const;
        bool isInit() const;
                
        QByteArray saveGeometry();
        bool restoreGeometry(const QByteArray&);
        QByteArray saveState();
        bool restoreState(const QByteArray&);
        
    public slots:
        void getModuleWidgets(core::Module::WidgetType, QWidget*, QVector<QPair<QString, QWidget*> >&);
        
    protected:
        bool iInit(QWidget*);

    private slots:
        void clearOptions();
        
    private:
        WdgLogbook*	m_logbook;
        WdgToolbar* m_toolbar;
        WdgSidebar* m_sidebar;
        WdgOptions* m_options;
    };
}

#endif // LOGBOOK_LOGBOOKMODULE_H

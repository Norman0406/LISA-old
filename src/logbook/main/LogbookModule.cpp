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
        : Module(), m_toolbar(0), m_sidebar(0), m_options(0)
    {
        setupUi(this);
    }

    LogbookModule::~LogbookModule(void)
    {
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
        return m_toolbar && m_sidebar &&
            Module::isInit();
    }

    bool LogbookModule::iInit(QWidget* parent)
    {        
        m_toolbar = new WdgToolbar(parent);
        if (!m_toolbar)
            return false;
        
        m_sidebar = new WdgSidebar(parent);
        if (!m_sidebar)
            return false;
                
        // add a default log entry
        addNewEntry(0);
        
        editButton->setChecked(false);
        showLogEntries(editButton->isChecked());

        // init database layout
        initDatabaseLayout();
                
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
            widgets.push_back(QPair<QString, QWidget*>(getDisplayName(), this));
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
    
    void LogbookModule::initDatabaseLayout()
    {
        QTableView* table = tableView;

        QStandardItemModel* model = new QStandardItemModel(this);
        model->setHorizontalHeaderItem(0, new QStandardItem("Date"));
        model->setHorizontalHeaderItem(1, new QStandardItem("Start"));
        model->setHorizontalHeaderItem(2, new QStandardItem("Callsign"));
        model->setHorizontalHeaderItem(3, new QStandardItem("Sent"));
        model->setHorizontalHeaderItem(4, new QStandardItem("Rcvd"));
        model->setHorizontalHeaderItem(5, new QStandardItem("Freq"));
        model->setHorizontalHeaderItem(6, new QStandardItem("Band"));
        model->setHorizontalHeaderItem(7, new QStandardItem("Mode"));
        model->setHorizontalHeaderItem(8, new QStandardItem("Name"));
        model->setHorizontalHeaderItem(9, new QStandardItem("Country"));
        model->setHorizontalHeaderItem(10, new QStandardItem("Locator"));
        model->setHorizontalHeaderItem(11, new QStandardItem("Distance"));
        model->setHorizontalHeaderItem(12, new QStandardItem("Comment"));
        
        table->setModel(model);
    }
        
    void LogbookModule::addNewEntry(int index)
    {
        // create a new entry, if "+" tab is pressed
        if (index == tabWidget->count() - 1) {
            int position = tabWidget->count() - 1;
            WdgLogEntry* entry = new WdgLogEntry(this);

            // connect
            QObject::connect(entry, &WdgLogEntry::tabNameChanged, this, &LogbookModule::changeTabName);

            tabWidget->insertTab(position, entry, "New entry");
            tabWidget->setCurrentIndex(position);

            // remove close button on first tab
            if (tabWidget->count() <= 2) {
                m_tabBarCloseButton = tabWidget->tabBar()->tabButton(0, QTabBar::RightSide);
                tabWidget->tabBar()->setTabButton(0, QTabBar::RightSide, 0);
            }
            
            //tabWidget->tabBar()->tabButton(position, QTabBar::RightSide)->setFixedSize(12, 12);

            // remove close button on "+" tab
            tabWidget->tabBar()->setTabButton(position + 1, QTabBar::RightSide, 0);
                    
            // restore close button on first tab
            if (tabWidget->count() > 2 && m_tabBarCloseButton) {
                tabWidget->tabBar()->setTabButton(0, QTabBar::RightSide, m_tabBarCloseButton);
                m_tabBarCloseButton = 0;
            }
        }
    }

    void LogbookModule::closeLogEntry(int index)
    {
        // find log entry and cancel changes
        QList<WdgLogEntry*> entries = tabWidget->findChildren<WdgLogEntry*>();
        for (int i = 0; i < entries.size(); i++) {
            if (i == index) {
                WdgLogEntry* entry = entries[i];
                entry->cancel();
                break;
            }
        }
        
        // select appropriate tab
        if (index == tabWidget->count() - 2)
            tabWidget->setCurrentIndex(index - 1);
        else if (tabWidget->count() > 1)
            tabWidget->setCurrentIndex(index);
        else if (tabWidget->count() <= 1)
            tabWidget->setCurrentIndex(0);
        
        // remove tab
        tabWidget->removeTab(index);
        
        // remove close button on first tab
        if (tabWidget->count() <= 2) {
            m_tabBarCloseButton = tabWidget->tabBar()->tabButton(0, QTabBar::RightSide);
            tabWidget->tabBar()->setTabButton(0, QTabBar::RightSide, 0);
        }
    }

    void LogbookModule::showLogEntries(bool checked)
    {
        if (checked)
            tabWidget->setVisible(true);
        else
            tabWidget->setVisible(false);
    }
    
    void LogbookModule::changeTabName(QString name, const WdgLogEntry* entry)
    {
        // UNDONE: does not work always with multiple tabs
        QList<WdgLogEntry*> entries = tabWidget->findChildren<WdgLogEntry*>();
        for (int i = 0; i < entries.size(); i++) {
            WdgLogEntry* curEntry = entries[i];
            if (curEntry == entry) {
                tabWidget->setTabText(i, name);
                break;
            }
        }
    }
}

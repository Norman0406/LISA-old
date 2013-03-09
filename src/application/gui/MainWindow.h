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

#ifndef LISA_MAINWINDOW_H
#define LISA_MAINWINDOW_H

#include <core/main/Module.h>
#include <core/common/Logging.h>
#include "ui_MainWindow.h"

namespace lisa
{
    class WdgLogging;
    class System;

    class MainWindow
        : public QMainWindow, public Ui::MainWindow
    {
        Q_OBJECT

    public:
        MainWindow(QWidget* parent = 0);
        ~MainWindow(void);

    public slots:
        void showAboutDlg();
        void showOptionsDlg();
        void newLoggingEntry(const core::LoggingEntry&);
        void addModuleWidget(core::Module::WidgetType, const QString&, QWidget*);
        
    signals:
        void createOptionWidgets(QVector<QPair<QString, core::OptionsBase*> >&, QWidget*);
        void rebuildSettingsPages();
        
    protected:
        bool iInit();

    private:
        WdgLogging* m_wdgLogging;

    };
}

#endif // LISA_MAINWINDOW_H

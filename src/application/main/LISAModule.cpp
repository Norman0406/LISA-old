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

#include "../gui/DlgAbout.h"
#include "../gui/DlgOptions.h"
#include "../gui/WdgLogging.h"
#include "../gui/WdgOptions.h"
#include "LISAModule.h"
#include "System.h"
#include <QtCore/QFile>

namespace lisa
{
    LISAModule::LISAModule()
        : Module(), m_mainWindow(0)
    {
        addProperty("Style", QApplication::style()->objectName());
    }
    
    LISAModule::~LISAModule(void)
    {
        delete m_mainWindow;
    }
    
    QString	LISAModule::getModuleName() const
    {
        return "LISA";
    }

    QString LISAModule::getDisplayName() const
    {
        return "LISA";
    }

    bool LISAModule::isInit() const
    {
        return m_mainWindow &&
            Module::isInit();
    }
    
    bool LISAModule::createWindow()
    {
        if (m_mainWindow)
            return false;

        m_mainWindow = new MainWindow(0);
        if (!m_mainWindow)
            return false;

        return true;
    }

    bool LISAModule::iInit(QWidget* parent)
    {
        if (!m_mainWindow)
            return false;

        // does not add any widgets yet
        Q_UNUSED(parent);

        return true;
    }
    
    void LISAModule::createOptionWidgets(QVector<QPair<QString, core::OptionsBase*> >& widgets, QWidget* parent)
    {
        WdgOptions* wdgOpt = new WdgOptions(&m_properties, this, parent);
        connect(wdgOpt, &WdgOptions::fillDetectedModules, this, &LISAModule::fillDetectedModules,
            Qt::DirectConnection);
        connect(wdgOpt, &WdgOptions::moduleLoaded, this, &LISAModule::moduleLoaded,
            Qt::DirectConnection);
        connect(wdgOpt, &WdgOptions::enableModule, this, &LISAModule::enableModule);
        wdgOpt->init();
        widgets.push_back(QPair<QString, core::OptionsBase*>(getDisplayName(), wdgOpt));
    }
    
    MainWindow* LISAModule::getWindow()
    {
        return m_mainWindow;
    }
    
    QByteArray LISAModule::saveGeometry()
    {
        return m_mainWindow->saveGeometry();
    }

    bool LISAModule::restoreGeometry(const QByteArray& geometry)
    {
        return m_mainWindow->restoreGeometry(geometry);
    }
    
    QByteArray LISAModule::saveState()
    {
        return m_mainWindow->saveState();
    }

    bool LISAModule::restoreState(const QByteArray& state)
    {
        return m_mainWindow->restoreState(state);
    }
}

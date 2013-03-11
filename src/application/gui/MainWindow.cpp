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

#include "DlgAbout.h"
#include "DlgOptions.h"
#include "WdgLogging.h"
#include "WdgOptions.h"
#include "MainWindow.h"
#include <core/common/FileUtils.h>
#include <core/main/Module.h>
#include <QtCore/QFile>

namespace lisa
{
    MainWindow::MainWindow(QWidget* parent)
        : QMainWindow(parent), m_wdgLogging(0)
    {
        addProperty("Style", QApplication::style()->objectName());

        setupUi(this);

        appSidebarWidgets->removeItem(0);
        
        // add toolbar toggles to "View" menu
        QList<QMenu*> entries = appMenuBar->findChildren<QMenu*>();
        for (QList<QMenu*>::const_iterator it = entries.begin(); it != entries.end(); it++) {
            QMenu* curMenu = *it;
            if (curMenu->title() == "View") {
                curMenu->addAction(appToolbar->toggleViewAction());
                curMenu->addAction(appSidebar->toggleViewAction());
                curMenu->addAction(appLogging->toggleViewAction());
                curMenu->addSeparator();
                break;
            }
        }
        
        // add logging widget to dock widget
        m_wdgLogging = new WdgLogging(this);
        appLoggingLayout->addWidget(m_wdgLogging);
        
        init();
    }
    
    MainWindow::~MainWindow(void)
    {
        qDebug() << "shutting down system";

        saveProperties("Main");
        saveState();
        
        // delete all registered modules
        for (int i = 0; i < m_modules.size(); i++) {
            core::Module* mod = m_modules[i];
            mod->saveProperties(mod->getModuleName());            
            delete mod;
        }

        // delete main window at last
        disconnect(m_logging, &core::Logging::newLoggingEntry,
            this, &MainWindow::newLoggingEntry);
        
        m_modules.clear();
        
        delete m_logging;
    }
        
    void MainWindow::showAboutDlg()
    {
        DlgAbout dlg;
        dlg.setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint | Qt::WindowTitleHint | Qt::WindowStaysOnTopHint);
        dlg.exec();	// shows a modal dialog
    }
    
    void MainWindow::showOptionsDlg()
    {
        DlgOptions dlg;

        QVector<QPair<QString, core::OptionsBase*> > widgets;

        // create the main window option widget
        WdgOptions* wdgOpt = new WdgOptions(&m_properties, &dlg);

        // tell the widget which modules exist and which of them are currently loaded
        QVector<QPair<QString, bool> > modules;
        for (QMap<QString, QString>::const_iterator it = m_detectedModules.begin(); it != m_detectedModules.end(); it++) {
            QString moduleName = it.key();
            modules.push_back(QPair<QString, bool>(moduleName, isModuleLoaded(moduleName)));
        }
        wdgOpt->init(modules);

        connect(wdgOpt, &WdgOptions::enableModule, this, &MainWindow::enableModule);
        widgets.push_back(QPair<QString, core::OptionsBase*>("General", wdgOpt));

        // add module option widgets
        for (int i = 0; i < m_modules.size(); i++) {
            core::Module* module = m_modules[i];
            QVector<QPair<QString, QWidget*> > modOpt;
            module->getModuleWidgets(core::Module::WT_OPTIONS, &dlg, modOpt);

            for (int i = 0; i < modOpt.size(); i++) {
                core::OptionsBase* options = (core::OptionsBase*)modOpt[i].second;
                connect(options, &core::OptionsBase::destroyed, &dlg, &DlgOptions::removeWidget);
                widgets.push_back(QPair<QString, core::OptionsBase*>(modOpt[i].first, options));
            }
        }
        connect(this, &MainWindow::moduleLoaded, &dlg, &DlgOptions::addWidget);
        
        // show options dialog
        dlg.init(widgets);
        dlg.setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint | Qt::WindowTitleHint | Qt::WindowStaysOnTopHint);
        dlg.exec();
    }
    
    void MainWindow::newLoggingEntry(const core::LoggingEntry& entry)
    {
        if (m_wdgLogging)
            m_wdgLogging->addLogEntry(entry);
    }
    
    void MainWindow::loadState()
    {
        QString folder = core::FileUtils::openFolder(core::SF_CONFIG, false);

        if (folder.isEmpty())
            return;

        QString filename = folder + "layout.bin";
        QFile file(filename);

        if (file.open(QFile::ReadOnly)) {
            qDebug() << "loading system state from " << filename;
                        
            uchar mainGeomSize = 0;
            file.getChar((char*)&mainGeomSize);
            QByteArray mainGeom = file.read(mainGeomSize);
            QMainWindow::restoreGeometry(mainGeom);
            
            uchar mainStateSize = 0;
            file.getChar((char*)&mainStateSize);
            QByteArray mainState = file.read(mainStateSize);
            QMainWindow::restoreState(mainState);

            // load geometry and state information for each module
            uchar moduleCount = 0;
            file.getChar((char*)&moduleCount);

            for (int i = 0; i < moduleCount; i++) {
                // read module name
                uchar moduleNameSize = 0;
                file.getChar((char*)&moduleNameSize);
                QString moduleName(file.read(moduleNameSize));
                std::string name = moduleName.toStdString();

                // read state information
                uchar geometrySize = 0;
                file.getChar((char*)&geometrySize);
                QByteArray geometry = file.read(geometrySize);

                uchar stateSize = 0;
                file.getChar((char*)&stateSize);
                QByteArray state = file.read(stateSize);
                
                // save state information for later use, when creating module instances
                QPair<QByteArray, QByteArray> stateInfo(geometry, state);

                if (m_stateInfo.find(moduleName) != m_stateInfo.end()) {
                    // Warning: there are more modules with the same name
                }

                m_stateInfo[moduleName] = stateInfo;
            }
        }
        else
            qWarning() << "could not load system state from " << filename;
    }

    void MainWindow::saveState()
    {
        QString folder = core::FileUtils::openFolder(core::SF_CONFIG, true);

        if (folder.isEmpty())
            return;
        
        QString filename = folder + "layout.bin";
        QFile file(filename);

        if (file.open(QFile::WriteOnly)) {
            qDebug() << "saving system state to " << filename;
            
            // save geometry and state information for main window
            QByteArray mainGeom = QMainWindow::saveGeometry();
            QByteArray mainState = QMainWindow::saveState();
            
            // write state information
            file.putChar(mainGeom.size());
            file.write(mainGeom);
            file.putChar(mainState.size());
            file.write(mainState);
            
            file.putChar(m_modules.size());

            // save geometry and state information for each module
            for (int i = 0; i < m_modules.size(); i++) {
                core::Module* module = m_modules[i];
            
                // write module name
                file.putChar(module->getModuleName().toLocal8Bit().size());
                file.write(module->getModuleName().toLocal8Bit());
                
                // get state information
                QByteArray geometry = module->saveGeometry();
                QByteArray state = module->saveState();

                // write state information
                file.putChar(geometry.size());
                file.write(geometry);
                file.putChar(state.size());
                file.write(state);
            }
        }
        else
            qWarning() << "could not save system state to " << filename;
    }
    
    void MainWindow::detectModules()
    {
        qDebug() << "loading modules";

        QDir modulesDir(qApp->applicationDirPath());
                
        // iterate over file list in the directory
        QStringList files = modulesDir.entryList(QDir::Files);
        for (int i = 0; i < files.size(); i++) {
            QString filename = files[i];

            std::string temp = filename.toStdString();
            std::string dir = modulesDir.path().toStdString();

            // try to load the file as a plugin
            QPluginLoader loader(modulesDir.absoluteFilePath(filename));
            QObject* module = loader.instance();
                        
            // check if the interface matches
            if (module) {
                core::ModuleBase* modInterface = qobject_cast<core::ModuleBase*>(module);

                // add the plugin to the list
                if (modInterface) {
                    qDebug() << "found module: " << modInterface->getModuleName() << " in " << filename;

                    m_detectedModules[modInterface->getModuleName()] = loader.fileName();
                    std::string tmp = loader.fileName().toStdString();
                    delete modInterface;
                }
            }
        }
    }
    
    void MainWindow::loadModules()
    {
        for (QMap<QString, QString>::const_iterator it = m_detectedModules.begin();
            it != m_detectedModules.end(); it++) {
                // TODO: skip modules which are not enabled at runtime (read from settings)

                loadModule(it.value());
        }
    }

    core::Module* MainWindow::loadModule(const QString& filename)
    {
        // try to load the file as a plugin
        QPluginLoader loader(filename);
        QObject* module = loader.instance();
                        
        // check if the interface matches
        if (module) {
            core::ModuleBase* modInterface = qobject_cast<core::ModuleBase*>(module);

            // add the plugin to the list
            if (modInterface) {
                m_modules.push_back(static_cast<core::Module*>(modInterface));
                return (core::Module*)modInterface;
            }
        }

        return 0;
    }
    
    void MainWindow::enableModule(const QString& moduleName, bool enabled)
    {
        if (enabled) {
            if (isModuleLoaded(moduleName))
                return;

            // create the module instance and init it
            QMap<QString, QString>::const_iterator it = m_detectedModules.find(moduleName);
            if (it == m_detectedModules.end())
                qWarning() << "could not find module " << moduleName;
            else {
                core::Module* module = loadModule(it.value());
                
                if (!initModule(module)) {
                    removeModule(module);
                    module->deleteLater();
                    qCritical() << "could not initialize module " << moduleName;
                    return;
                }

                // TODO: load module state

                // TODO: there's a problem with OptionsBase::destroyed signal causing DlgOptions::removeWidget() to be called
                //applyModuleProperties(module);

                // NOTE: or tell all other modules?
                module->postInitAll();

                emit moduleLoaded(module);
            }
        }
        else {
            if (!isModuleLoaded(moduleName))
                return;

            // find the module and delete it's instance
            bool deleted = false;
            for (QVector<core::Module*>::iterator it = m_modules.begin(); it != m_modules.end();) {
                if ((*it)->getModuleName() == moduleName) {

                    // TODO: save module state

                    (*it)->saveProperties((*it)->getModuleName());

                    (*it)->deleteLater();
                    it = m_modules.erase(it);
                    deleted = true;
                    break;
                }
                else
                    it++;
            }

            if (!deleted)
                qWarning() << "could not find module " << moduleName;
        }
    }
        
    bool MainWindow::isModuleLoaded(const QString& moduleName)
    {
        for (int i = 0; i < m_modules.size(); i++) {
            if (m_modules[i]->getModuleName() == moduleName)
                return true;
        }
        return false;
    }

    void MainWindow::isModuleLoaded(const QString& moduleName, bool& loaded)
    {
        loaded = isModuleLoaded(moduleName);
    }
    
    bool MainWindow::removeModule(core::Module* module)
    {
        for (QVector<core::Module*>::iterator it = m_modules.begin(); it != m_modules.end(); it++) {
            if (*it == module) {
                it = m_modules.erase(it);
                return true;
            }
            else
                it++;
        }
        return false;
    }
    
    bool MainWindow::initModule(core::Module* module)
    {
        // in case MainModule is being intialized, we won't set a valid parent widget
        // otherwise, MainWindow is the parent widget

        /*        
        // register message handling functions with the system
        //connect(module, &core::Module::msgRegister, this, &System::msgRegister);
        //connect(module, &core::Module::msgSend, this, &System::msgSend);
        */

        // init module
        if (!module->init(this))
            return false;

        // add main widgets to window
        QVector<QPair<QString, QWidget*> > mainWidgets;
        module->getModuleWidgets(core::Module::WT_MAIN, this, mainWidgets);
        for (QVector<QPair<QString, QWidget*> >::const_iterator it = mainWidgets.begin(); it != mainWidgets.end(); it++)
            appMainWidgets->addTab(it->second, it->first);

        // add toolbar widgets to window
        QVector<QPair<QString, QWidget*> > toolbarWidgets;
        module->getModuleWidgets(core::Module::WT_TOOLBAR, this, toolbarWidgets);
        for (QVector<QPair<QString, QWidget*> >::const_iterator it = toolbarWidgets.begin(); it != toolbarWidgets.end(); it++)
            appToolbarWidgets->addTab(it->second, it->first);
        
        // add sidebar widgets to window
        QVector<QPair<QString, QWidget*> > sidebarWidgets;
        module->getModuleWidgets(core::Module::WT_SIDEBAR, this, sidebarWidgets);
        for (QVector<QPair<QString, QWidget*> >::const_iterator it = sidebarWidgets.begin(); it != sidebarWidgets.end(); it++)
            appSidebarWidgets->addItem(it->second, it->first);

        // restore module state if possible
        if (m_stateInfo.find(module->getModuleName()) != m_stateInfo.end()) {
            const QPair<QByteArray, QByteArray>& stateInfo = m_stateInfo[module->getModuleName()];
            module->restoreGeometry(stateInfo.first);
            module->restoreState(stateInfo.second);
        }

        // check if module is correctly initialized
        if (!module->isInit()) {
            qCritical() << "module is not initialized";
            return false;
        }
        
        return true;
    }
    
    bool MainWindow::initModules()
    {
        for (int i = 0; i < m_modules.size(); i++) {
            core::Module* mod = m_modules[i];
            
            if (!initModule(mod)) {
                removeModule(mod);
                delete mod;
                return false;
            }
        }
        
        // tell modules that all modules have been initialized
        for (int i = 0; i < m_modules.size(); i++) {
            m_modules[i]->postInitAll();
        }

        return true;
    }
    
    bool MainWindow::init()
    {
        // init logging
        m_logging = core::Logging::instance();
        
        loadState();
        loadProperties("Main");
                
        // load other plugins
        detectModules();
        loadModules();
        
        // init modules
        if (!initModules())
            return false;

        // connect logger to logging widget and set previous logging entries
        const QVector<core::LoggingEntry>& entries = m_logging->getEntries();
        for (int i = 0; i < entries.size(); i++)
            newLoggingEntry(entries[i]);
        connect(m_logging, &core::Logging::newLoggingEntry, this, &MainWindow::newLoggingEntry);
        
        // apply loaded properties for all modules
        applyProperties();

        return true;
    }
    
    void MainWindow::applyProperties()
    {
        // apply main window options
        WdgOptions* wdgOpt = new WdgOptions(&m_properties, this);
        wdgOpt->apply();
        wdgOpt->deleteLater();

        // apply module options
        for (int i = 0; i < m_modules.size(); i++) {
            core::Module* module = m_modules[i];
            applyModuleProperties(module);
        }
    }

    void MainWindow::applyModuleProperties(core::Module* module)
    {
        QVector<QPair<QString, QWidget*> > modOpt;
        module->getModuleWidgets(core::Module::WT_OPTIONS, this, modOpt);

        for (int i = 0; i < modOpt.size(); i++) {
            ((core::OptionsBase*)modOpt[i].second)->apply();
            modOpt[i].second->deleteLater();
        }
    }
}

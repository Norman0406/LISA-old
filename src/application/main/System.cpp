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

#include "System.h"
#include "LISAModule.h"
#include "../gui/MainWindow.h"
#include <core/common/FileUtils.h>
#include <core/main/Module.h>
#include <QtCore/QFile>

// define memory dumping when using Visual Studio
#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define new new(1, __FILE__, __LINE__)
#define MEMDUMP _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

namespace lisa
{
    System* System::m_instance = 0;

    System::System(int argc, char *argv[])
        : QObject(0), m_application(argc, argv),
        m_mainModule(0), m_logging(0)
    {
    }

    System::~System(void)
    {
        qDebug() << "shutting down system";
        
        MainWindow* mainWindow = m_mainModule->getWindow();

        // delete all registered modules
        for (int i = 0; i < m_modules.size(); i++) {
            core::Module* mod = m_modules[i];
            mod->saveProperties();
            
            // disable module adding
            disconnect(mod, &core::Module::moduleWidgetAdded, mainWindow, &MainWindow::addModuleWidget);

            // delete main module at last
            if (mod == m_mainModule)
                continue;

            delete mod;
        }

        // delete main window at last
        disconnect(m_logging, &core::Logging::newLoggingEntry,
            mainWindow, &MainWindow::newLoggingEntry);
        delete m_mainModule;
        
        m_modules.clear();
        
        delete m_logging;
    }

    void System::loadState()
    {
        QString folder = core::FileUtils::openFolder(core::SF_CONFIG, false);

        if (folder.isEmpty())
            return;

        QString filename = folder + "layout.bin";
        QFile file(filename);

        if (file.open(QFile::ReadOnly)) {
            qDebug() << "loading system state from " << filename;

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

    void System::saveState()
    {
        QString folder = core::FileUtils::openFolder(core::SF_CONFIG, true);

        if (folder.isEmpty())
            return;
        
        QString filename = folder + "layout.bin";
        QFile file(filename);

        if (file.open(QFile::WriteOnly)) {
            qDebug() << "saving system state to " << filename;
            
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
    
    void System::detectModules()
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

    void System::loadModules()
    {
        for (QMap<QString, QString>::const_iterator it = m_detectedModules.begin();
            it != m_detectedModules.end(); it++) {
                // TODO: skip modules which are not enabled at runtime (read from settings)

                loadModule(it.value());
        }
    }

    core::Module* System::loadModule(const QString& filename)
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
    
    void System::enableModule(const QString& moduleName, bool enabled)
    {
        if (moduleName == m_mainModule->getModuleName())
            return;

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
                    delete module;
                    qCritical() << "could not initialize module " << moduleName;
                    return;
                }

                // NOTE: or tell all other modules?
                module->postInitAll();
            }
        }
        else {
            if (!isModuleLoaded(moduleName))
                return;

            // find the module and delete it's instance
            bool deleted = false;
            for (QVector<core::Module*>::iterator it = m_modules.begin(); it != m_modules.end();) {
                if ((*it)->getModuleName() == moduleName) {
                    delete *it;
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

    void System::fillDetectedModule(QVector<QString>& modules)
    {
        // push module names to vector
        for (QMap<QString, QString>::const_iterator it = m_detectedModules.begin();
            it != m_detectedModules.end(); it++) {
                modules.push_back(it.key());
        }
    }
    
    bool System::isModuleLoaded(const QString& moduleName)
    {
        for (int i = 0; i < m_modules.size(); i++) {
            if (m_modules[i]->getModuleName() == moduleName)
                return true;
        }
        return false;
    }

    void System::moduleLoaded(const QString& moduleName, bool& loaded)
    {
        loaded = isModuleLoaded(moduleName);
    }
    
    bool System::removeModule(core::Module* module)
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
    
    bool System::initModule(core::Module* module)
    {
        if (!m_mainModule)
            return false;

        QWidget* parent = 0;

        // in case MainModule is being intialized, we won't set a valid parent widget
        // otherwise, MainWindow is the parent widget

        if (module != m_mainModule)
            parent = m_mainModule->getWindow();
        else {
            // the main module has to create the window before any other module, so that they can call the signal and
            // dynamically add widgets to the main window during initialization.
            m_mainModule->createWindow();
        }
                    
        MainWindow* mainWindow = m_mainModule->getWindow();
        if (!mainWindow)
            return false;

        // connect module to the main window
        connect(module, &core::Module::moduleWidgetAdded, mainWindow, &MainWindow::addModuleWidget);
        
        // register message handling functions with the system
        connect(module, &core::Module::msgRegister, this, &System::msgRegister);
        connect(module, &core::Module::msgSend, this, &System::msgSend);

        // connect module to the options dialog in the main window			
        connect(mainWindow, &MainWindow::createOptionWidgets, module, &core::Module::createOptionWidgets);
        
        // init module
        if (!module->init(parent))
            return false;

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
    
    bool System::initModules()
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

    System* System::init(int argc, char *argv[])
    {
        if (!m_instance) {
            m_instance = new System(argc, argv);
            if (!m_instance->init()) {
                delete m_instance;
                m_instance = 0;
                return 0;
            }
        }

        return m_instance;
    }

    bool System::init()
    {
        if (m_mainModule)
            return true;

        // init logging
        m_logging = core::Logging::instance();
        
        loadState();
        
        qDebug() << "creating main module";
        m_mainModule = new LISAModule();
        if (!m_mainModule) {
            qCritical() << "could not create main module";
            return false;
        }
        connect(m_mainModule, &LISAModule::fillDetectedModules, this, &System::fillDetectedModule,
            Qt::DirectConnection);
        connect(m_mainModule, &LISAModule::moduleLoaded, this, &System::moduleLoaded,
            Qt::DirectConnection);
        connect(m_mainModule, &LISAModule::enableModule, this, &System::enableModule);

        m_modules.push_back(m_mainModule);
        
        // load other plugins
        detectModules();
        loadModules();
        
        // init modules
        if (!initModules())
            return false;

        // connect logger to logging widget and set previous logging entries
        MainWindow* mainWindow = m_mainModule->getWindow();
        const QVector<core::LoggingEntry>& entries = m_logging->getEntries();
        for (int i = 0; i < entries.size(); i++)
            mainWindow->newLoggingEntry(entries[i]);
        connect(m_logging, &core::Logging::newLoggingEntry,
            mainWindow, &MainWindow::newLoggingEntry, Qt::QueuedConnection);
        /*connect(mainWindow, &MainWindow::enableModule,
            this, &System::enableModule);*/
        
        // apply loaded properties for all modules
        applyProperties();

        return true;
    }

    void System::applyProperties()
    {
        // iterate through registered modules and get option widgets
        for (int i = 0; i < m_modules.size(); i++) {
            core::Module* mod = m_modules[i];

            // create an option widget with no parent (don't forget to delete later)
            QVector<QPair<QString, core::OptionsBase*> > widgets;
            mod->createOptionWidgets(widgets, 0);

            // apply properties for each single option widget
            for (int i = 0; i < widgets.size(); i++) {
                widgets[i].second->apply();
                delete widgets[i].second;
            }
        }
    }
    
    void System::msgRegister(QString id)
    {
        // get the sender
        core::Module* module = (core::Module*)qobject_cast<core::ModuleBase*>(sender());

        if (module) {
            QVector<core::Module*>& modules = m_registeredMessages[id];

            // check if this module already registered for this specific message id
            if (modules.size() > 0) {
                for (int i = 0; i < modules.size(); i++) {
                    const core::Module* mod = modules[i];
                    if (mod == module) {
                        qWarning() << "module " << module->getModuleName() << " already registered for message " << id;
                        return;
                    }
                }
            }

            qDebug() << "registering message " << id << " with module " << module->getModuleName();

            // add registered message
            modules.push_back(module);
        }
    }

    void System::msgSend(QString id, const QVariant& value)
    {
        // check if this message has been registered
        QMap<QString, QVector<core::Module*> >::const_iterator msg = m_registeredMessages.find(id);

        if (msg != m_registeredMessages.end()) {
            const QVector<core::Module*>& modules = msg.value();

            // send this message to all registered modules
            for (int i = 0; i < modules.size(); i++) {
                core::Module* mod = modules[i];
                mod->msgReceive(id, value);
            }
        }
    }

    int System::run()
    {
        try {
            if (!m_mainModule || !m_mainModule->isInit())
                return 1;

            // show and process main application
            MainWindow* mainWindow = m_mainModule->getWindow();
            mainWindow->show();

            qDebug() << "starting application";
            int retVal = m_application.exec();

            saveState();

            return retVal;
        }
        catch (core::Exception& e) {
            e.show();
        }

#ifdef _MSC_VER
        MEMDUMP;
#endif

        return 1;
    }
}

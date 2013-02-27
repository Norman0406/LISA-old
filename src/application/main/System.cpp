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
		: m_application(argc, argv),
		m_mainModule(0), m_logging(0)
	{
	}

	System::~System(void)
	{
		qDebug() << "shutting down system";

		// delete all registered modules
		for (int i = 0; i < m_modules.size(); i++) {
			core::Module* mod = m_modules[i];
			mod->saveProperties();

			// delete main module at last
			if (mod == m_mainModule)
				continue;

			delete mod;
		}

		// delete main window at last
		MainWindow* mainWindow = m_mainModule->getWindow();
		QObject::disconnect(m_logging, &core::Logging::newLoggingEntry,
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
	
	void System::loadModulePlugins()
	{
		qDebug() << "loading modules";

		QDir modulesDir(qApp->applicationDirPath());

		// necessary?
/*#if defined(Q_OS_WIN)
	 if (modulesDir.dirName().toLower() == "debug" || modulesDir.dirName().toLower() == "release")
		 modulesDir.cdUp();
 #elif defined(Q_OS_MAC)
	 if (modulesDir.dirName() == "MacOS") {
		 modulesDir.cdUp();
		 modulesDir.cdUp();
		 modulesDir.cdUp();
	 }
 #endif*/

		//modulesDir.cd("modules");
		
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
					m_modules.push_back(static_cast<core::Module*>(modInterface));
				}
			}
		}
	}
	
	QVector<core::Module*>& System::getModules()
	{
		return m_modules;
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
		
		// init module
		if (!module->init(this, parent))
			return false;

		MainWindow* mainWindow = m_mainModule->getWindow();
		if (!mainWindow)
			return false;
		
		// add menu entries
		QList<QMenu*> menus = module->getMenus(mainWindow);
		for (QList<QMenu*>::const_iterator it = menus.begin();
			it != menus.end(); it++)
			mainWindow->addMenu(*it);
		
		// add main widgets
		QList<QPair<QString, QWidget*>> mainWidgets = module->getMainWidgets(mainWindow);
		for (QList<QPair<QString, QWidget*>>::const_iterator it = mainWidgets.begin();
			it != mainWidgets.end(); it++)
			mainWindow->addMainWidget(it->second, it->first);

		// add toolbar widgets
		QList<QPair<QString, QWidget*>> toolbarWidgets = module->getToolbarWidgets(mainWindow);
		for (QList<QPair<QString, QWidget*>>::const_iterator it = toolbarWidgets.begin();
			it != toolbarWidgets.end(); it++)
			mainWindow->addToolbarWidget(it->second, it->first);

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

		m_modules.push_back(m_mainModule);
		
		// load other plugins
		loadModulePlugins();
		
		// init modules
		if (!initModules())
			return false;

		// connect logger to logging widget and set previous logging entries
		MainWindow* mainWindow = m_mainModule->getWindow();
		const QVector<core::LoggingEntry>& entries = m_logging->getEntries();
		for (int i = 0; i < entries.size(); i++)
			mainWindow->newLoggingEntry(entries[i]);
		QObject::connect(m_logging, &core::Logging::newLoggingEntry,
			mainWindow, &MainWindow::newLoggingEntry, Qt::QueuedConnection);

		// apply loaded properties for all modules
		m_mainModule->applyProperties();

		return true;
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
		//MEMDUMP;
#endif

		return 1;
	}
}

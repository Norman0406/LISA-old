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
	
	bool LISAModule::iInit(QWidget* parent)
	{
		m_mainWindow = new MainWindow(getSystem(), parent);
		if (!m_mainWindow)
			return false;

		return true;
	}
		
	bool LISAModule::applyProperties()
	{
		if (!m_mainWindow)
			return false;

		QVector<core::Module*>& modules = getSystem()->getModules();

		// apply module properties
		for (int i = 0; i < modules.size(); i++) {
			Module* mod = modules[i];
			core::OptionsBase* optWdg = mod->getOptionsWdg(m_mainWindow);
			optWdg->apply();
			delete optWdg;
		}

		return true;
	}
	
	MainWindow* LISAModule::getWindow()
	{
		return m_mainWindow;
	}
	
	core::OptionsBase* LISAModule::getOptionsWdg(QWidget* parent)
	{
		return new WdgOptions(&m_properties, parent);
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

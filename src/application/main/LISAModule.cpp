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
	
	void LISAModule::createOptionWidgets(QVector<QPair<QString, core::OptionsBase*>>& widgets, QWidget* parent)
	{
		widgets.push_back(QPair<QString, core::OptionsBase*>(getDisplayName(), new WdgOptions(&m_properties, parent)));
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

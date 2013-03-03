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
		delete m_logbook;
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
		widgets.push_back(QPair<QString, core::OptionsBase*>(getDisplayName(), new WdgOptions(&m_properties, parent)));
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

#include "../gui/WdgLogEntry.h"
#include "../gui/WdgOptions.h"
#include "../gui/WdgToolbar.h"
#include "LogbookModule.h"

namespace logbook
{
	LogbookModule::LogbookModule()
		: Module(), m_logbook(0)
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
		return true &&
			Module::isInit();
	}

	bool LogbookModule::iInit(QWidget* parent)
	{
		m_logbook = new WdgLogbook(parent);
		if (!m_logbook)
			return false;
		
		return true;
	}
	
	core::OptionsBase* LogbookModule::getOptionsWdg(QWidget* parent)
	{
		return new WdgOptions(&m_properties, parent);
	}
	
	QList<QMenu*> LogbookModule::getMenus(QWidget* parent) const
	{
		QList<QMenu*> menus;

		// add menu
		QMenu* menu = new QMenu(getModuleName(), parent);
		QAction* nothing = new QAction("No entries here", parent);
		menu->addAction(nothing);

		menus.push_back(menu);

		return menus;
	}

	QList<QPair<QString, QWidget*>> LogbookModule::getMainWidgets(QWidget* parent)
	{
		Q_UNUSED(parent);
		QList<QPair<QString, QWidget*>> mainWidgets;

		QPair<QString, QWidget*> wdgPair(getDisplayName(), m_logbook);
		mainWidgets.push_back(wdgPair);

		return mainWidgets;
	}
	
	QList<QPair<QString, QWidget*>> LogbookModule::getToolbarWidgets(QWidget* parent)
	{
		Q_UNUSED(parent);
		QList<QPair<QString, QWidget*>> toolbarWidgets;

		QPair<QString, QWidget*> wdgPair(getDisplayName(), new WdgToolbar(parent));
		toolbarWidgets.push_back(wdgPair);

		return toolbarWidgets;
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

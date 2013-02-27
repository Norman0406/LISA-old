#include "../gui/WdgOptions.h"
#include "../gui/WdgToolbar.h"
#include "DigitalModule.h"

namespace digital
{
	DigitalModule::DigitalModule()
		: Module()
	{
	}

	DigitalModule::~DigitalModule(void)
	{
	}
		
	QString	DigitalModule::getModuleName() const
	{
		return "Digital";
	}

	QString DigitalModule::getDisplayName() const
	{
		return "Digital Modes";
	}

	bool DigitalModule::isInit() const
	{
		return true &&
			Module::isInit();
	}

	bool DigitalModule::iInit(QWidget* parent)
	{
		m_digital = new WdgDigital(parent);
		if (!m_digital)
			return false;

		return true;
	}
	
	core::OptionsBase* DigitalModule::getOptionsWdg(QWidget* parent)
	{
		return new WdgOptions(&m_properties, parent);
	}
	
	QList<QMenu*> DigitalModule::getMenus(QWidget* parent) const
	{
		QList<QMenu*> menus;

		// add menu
		QMenu* menu = new QMenu(getModuleName(), parent);
		QAction* nothing = new QAction("No entries here", parent);
		menu->addAction(nothing);

		menus.push_back(menu);

		return menus;
	}

	QList<QPair<QString, QWidget*>> DigitalModule::getMainWidgets(QWidget* parent)
	{
	   Q_UNUSED(parent);

		QList<QPair<QString, QWidget*>> mainWidgets;

		QPair<QString, QWidget*> wdgPair(getDisplayName(), m_digital);
		mainWidgets.push_back(wdgPair);

		return mainWidgets;
	}
	
	QList<QPair<QString, QWidget*>> DigitalModule::getToolbarWidgets(QWidget* parent)
	{
		Q_UNUSED(parent);

		QList<QPair<QString, QWidget*>> toolbarWidgets;

		QPair<QString, QWidget*> wdgPair(getDisplayName(), new WdgToolbar(parent));
		toolbarWidgets.push_back(wdgPair);

		return toolbarWidgets;
	}

	QByteArray DigitalModule::saveGeometry()
	{
		return m_digital->saveGeometry();
	}

	bool DigitalModule::restoreGeometry(const QByteArray& geometry)
	{
		return m_digital->restoreGeometry(geometry);
	}
	
	QByteArray DigitalModule::saveState()
	{
		return m_digital->saveState();
	}

	bool DigitalModule::restoreState(const QByteArray& state)
	{
		return m_digital->restoreState(state);
	}
}

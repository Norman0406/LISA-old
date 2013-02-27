#include "../gui/WdgOptions.h"
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
		return m_digital && m_toolbar &&
			Module::isInit();
	}

	bool DigitalModule::iInit(QWidget* parent)
	{
		m_digital = new WdgDigital(parent);
		if (!m_digital)
			return false;

		addModuleWidget(core::Module::WT_MAIN, getDisplayName(), m_digital);

		m_toolbar = new WdgToolbar(parent);
		if (!m_toolbar)
			return false;

		addModuleWidget(core::Module::WT_TOOLBAR, getDisplayName(), m_toolbar);

		return true;
	}
	
	void DigitalModule::createOptionWidgets(QMap<QString, core::OptionsBase*>& widgets, QWidget* parent)
	{
		widgets[getDisplayName()] = new WdgOptions(&m_properties, parent);
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

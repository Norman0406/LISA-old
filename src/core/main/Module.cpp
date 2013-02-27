#include "Module.h"
#include "../common/FileUtils.h"
#include <application/main/System.h>

namespace core
{
	Module::Module()
		: m_system(0), m_isInit(false), m_parent(0)
	{
	}

	Module::~Module(void)
	{
	}
	
	bool Module::init(lisa::System* sys, QWidget* parent)
	{
		if (!sys)
			return false;

		m_system = sys;

		// has it already been init?
		if (m_isInit)
			return false;

		qDebug() << "initializing module: " << getModuleName();

		// load properties from file
		loadProperties();

		m_parent = parent;

		// init module
		if (iInit(parent))
			m_isInit = true;

		if (m_isInit)
			qDebug() << "module " << getModuleName() << " was successfully initialized";

		// was it successful?
		return m_isInit;
	}
	
	bool Module::isInit() const
	{
		return m_isInit && m_system;
	}
	
	lisa::System* Module::getSystem()
	{
		return m_system;
	}
	
	QList<QMenu*> Module::getMenus(QWidget* parent) const
	{
		Q_UNUSED(parent);

		// no menus by default
		return QList<QMenu*>();
	}

	QList<QPair<QString, QWidget*>> Module::getMainWidgets(QWidget* parent)
	{
		Q_UNUSED(parent);

		// no main widgets by default
		return QList<QPair<QString, QWidget*>>();
	}
	
	QList<QPair<QString, QWidget*>> Module::getToolbarWidgets(QWidget* parent)
	{
		Q_UNUSED(parent);

		// no toolbar widgets by default
		return QList<QPair<QString, QWidget*>>();
	}
	
	OptionsBase* Module::getOptionsWdg(QWidget* parent)
	{
		Q_UNUSED(parent);

		// no options widget by default
		return 0;
	}
	
	bool Module::loadProperties()
	{
		QString folder = FileUtils::openFolder(SF_CONFIG, false);

		if (!folder.isEmpty()) {
			QString filename = folder + getModuleName().toLower() + ".xml";
			
			qDebug() << "loading properties for module " << getModuleName() << " from " << filename;

			return m_properties.loadFromFile(filename, getModuleName());
		}

		return false;
	}

	bool Module::saveProperties()
	{
		QString folder = FileUtils::openFolder(SF_CONFIG, true);

		if (!folder.isEmpty()) {
			QString filename = folder + getModuleName().toLower() + ".xml";

			qDebug() << "saving properties for module " << getModuleName() << " to " << filename;

			return m_properties.saveToFile(filename, getModuleName());
		}

		return false;

	}
}

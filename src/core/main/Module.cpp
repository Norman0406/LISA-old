#include "Module.h"
#include "../common/FileUtils.h"

namespace core
{
	Module::Module()
		: m_isInit(false), m_parent(0)
	{
		qRegisterMetaType<core::Module::WidgetType>("core::Module::WidgetType");
	}

	Module::~Module(void)
	{
		for (int i = 0; i < m_moduleWidgets.size(); i++)
			delete m_moduleWidgets[i];
		m_moduleWidgets.clear();
	}
	
	bool Module::init(QWidget* parent)
	{		
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
	
	bool Module::postInitAll()
	{
		if (!isInit()) {
			qCritical() << "module not initialized before post init";
			return false;
		}

		iPostInitAll();

		if (!isInit()) {
			qCritical() << "module not initialized after post init";
			return false;
		}

		return true;
	}

	void Module::iPostInitAll()
	{
	}

	bool Module::isInit() const
	{
		return m_isInit;
	}
	
	void Module::addModuleWidget(WidgetType type, const QString& text, QWidget* widget)
	{
		ModuleWidget* modWdg = new ModuleWidget;
		modWdg->type = type;
		modWdg->text = text;
		modWdg->widget = widget;
		m_moduleWidgets.push_back(modWdg);

		emit moduleWidgetAdded(type, text, widget);
	}

	const QVector<Module::ModuleWidget*>& Module::getModuleWidgets()
	{
		return m_moduleWidgets;
	}
	
	QVector<Module::ModuleWidget*> Module::getModuleWidgets(WidgetType type)
	{
		QVector<Module::ModuleWidget*> result;
		for (int i = 0; i < m_moduleWidgets.size(); i++) {
			ModuleWidget* wdg = m_moduleWidgets[i];
			if (wdg->type == type)
				result.push_back(wdg);
		}
		return result;
	}
	
	void Module::createOptionWidgets(QMap<QString, core::OptionsBase*>& widgets, QWidget* parent)
	{
		// overload this function to add option widgets to the main application
		Q_UNUSED(widgets);
		Q_UNUSED(parent);
	}

	void Module::msgReceive(QString id, const QVariant& value)
	{
		// overload this function to receive registered messages
		Q_UNUSED(id);
		Q_UNUSED(value);
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

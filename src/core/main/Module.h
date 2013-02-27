#ifndef CORE_MODULE_H
#define CORE_MODULE_H

#include <QtWidgets/QMainWindow>
#include "../common/Exception.h"
#include "../common/Logging.h"
#include "PropertyList.h"
#include "OptionsBase.h"
#include "ModuleBase.h"

namespace lisa
{
	class System;
}

namespace core
{
	class Module
		: public ModuleBase
	{
		Q_OBJECT

	public:
		enum WidgetType
		{
			WT_MAIN,
			WT_TOOLBAR,
			WT_SIDEBAR,
		};
		
		struct ModuleWidget
		{
			WidgetType type;
			QString text;
			QWidget* widget;
		};

		virtual ~Module(void);
				
		// initializing
		bool init(lisa::System*, QWidget*);
		virtual bool isInit() const;
		
		const QVector<ModuleWidget*>& getModuleWidgets();
		QVector<ModuleWidget*> getModuleWidgets(WidgetType);
		
		// property management
		template <typename T>
		bool addProperty(const QString& name, const T& defaultVal);

		template <typename T>
		Property<T>* getProperty(const QString& name);
		
		bool loadProperties();
		bool saveProperties();
		
		virtual QByteArray saveGeometry() = 0;
		virtual bool restoreGeometry(const QByteArray&) = 0;
		virtual QByteArray saveState() = 0;
		virtual bool restoreState(const QByteArray&) = 0;

	public slots:
		virtual void createOptionWidgets(QMap<QString, core::OptionsBase*>&, QWidget*);

	signals:
		void moduleWidgetAdded(WidgetType, const QString&, QWidget*);

	protected:
		Module();

		lisa::System* getSystem();
		void addModuleWidget(WidgetType, const QString&, QWidget*);
		
		PropertyList m_properties;
		
	private:
		bool			m_isInit;
		lisa::System*	m_system;
		QWidget*		m_parent;
		QVector<ModuleWidget*> m_moduleWidgets;
	};
	
	template <typename T>
	bool Module::addProperty(const QString& name, const T& defaultVal)
	{
		return m_properties.addProperty(Property<T>(name, defaultVal));
	}
	
	template <typename T>
	Property<T>* Module::getProperty(const QString& name)
	{
		return m_properties.getProperty<T>(name);
	}
}

#endif // CORE_MODULE_H
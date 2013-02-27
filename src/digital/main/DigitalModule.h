#ifndef DIGITAL_DIGITALMODULE_H
#define DIGITAL_DIGITALMODULE_H

#include <core/main/Module.h>
#include "../gui/WdgDigital.h"

namespace digital
{
	class DigitalModule
		: public core::Module
	{
		Q_OBJECT
	    Q_PLUGIN_METADATA(IID ModuleBase_iid)
		Q_INTERFACES(core::ModuleBase)

	public:
		DigitalModule();
		~DigitalModule(void);

		QString	getModuleName() const;
		QString getDisplayName() const;
		bool isInit() const;

		core::OptionsBase* getOptionsWdg(QWidget*);
		QList<QMenu*> getMenus(QWidget*) const;
		QList<QPair<QString, QWidget*>> getMainWidgets(QWidget*);
		QList<QPair<QString, QWidget*>> getToolbarWidgets(QWidget*);
		
		QByteArray saveGeometry();
		bool restoreGeometry(const QByteArray&);
		QByteArray saveState();
		bool restoreState(const QByteArray&);
		
	protected:
		bool iInit(QWidget*);

	private:
		WdgDigital*	m_digital;
	};
}

#endif // DIGITAL_DIGITALMODULE_H

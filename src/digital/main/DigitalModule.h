#ifndef DIGITAL_DIGITALMODULE_H
#define DIGITAL_DIGITALMODULE_H

#include <core/main/Module.h>
#include "../gui/WdgDigital.h"
#include "../gui/WdgToolbar.h"
#include "../gui/WdgSidebar.h"

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

		QByteArray saveGeometry();
		bool restoreGeometry(const QByteArray&);
		QByteArray saveState();
		bool restoreState(const QByteArray&);

	public slots:
		void createOptionWidgets(QVector<QPair<QString, core::OptionsBase*>>& widgets, QWidget* parent);
				
	protected:
		bool iInit(QWidget*);

	private:
		WdgDigital*	m_digital;
		WdgToolbar* m_toolbar;
		WdgSidebar* m_sidebar;
	};
}

#endif // DIGITAL_DIGITALMODULE_H

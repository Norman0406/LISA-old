#ifndef LOGBOOK_LOGBOOKMODULE_H
#define LOGBOOK_LOGBOOKMODULE_H

#include <core/main/Module.h>
#include "../gui/WdgLogbook.h"
#include "../gui/WdgToolbar.h"
#include "../gui/WdgSidebar.h"

namespace logbook
{
	class LogbookModule
		: public core::Module
	{
		Q_OBJECT
		Q_PLUGIN_METADATA(IID ModuleBase_iid)
		Q_INTERFACES(core::ModuleBase)

	public:
		LogbookModule();
		~LogbookModule(void);

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
		WdgLogbook*	m_logbook;
		WdgToolbar* m_toolbar;
		WdgSidebar* m_sidebar;
	};
}

#endif // LOGBOOK_LOGBOOKMODULE_H

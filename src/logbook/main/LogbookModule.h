#ifndef LOGBOOK_LOGBOOKMODULE_H
#define LOGBOOK_LOGBOOKMODULE_H

#include <core/main/Module.h>
#include "../gui/WdgLogbook.h"

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
		WdgLogbook*	m_logbook;
	};
}

#endif // LOGBOOK_LOGBOOKMODULE_H

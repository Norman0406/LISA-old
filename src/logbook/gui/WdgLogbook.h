#ifndef LOGBOOK_WDGLOGBOOK_H
#define LOGBOOK_WDGLOGBOOK_H

#include <QtGui/QStandardItemModel>
#include "ui_WdgLogbook.h"

namespace logbook
{
	class WdgLogEntry;

	class WdgLogbook
		: public QMainWindow, public Ui::WdgLogbook
	{
		Q_OBJECT

	public:
		WdgLogbook(QWidget*);
		~WdgLogbook(void);

	public slots:
		void addNewEntry(int);
		void closeLogEntry(int);
		void showLogEntries(bool);
		void changeTabName(QString, const WdgLogEntry*);
				
	private:
		void initDatabaseLayout();

		QWidget*	m_tabBarCloseButton;

	};
}

#endif // LOGBOOK_WDGLOGBOOK_H
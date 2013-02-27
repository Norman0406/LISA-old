#ifndef LOGBOOK_WDGLOGENTRY_H
#define LOGBOOK_WDGLOGENTRY_H

#include "ui_WdgLogEntry.h"

namespace logbook
{
	class WdgLogEntry
		: public QWidget, public Ui::WdgLogEntry
	{
		Q_OBJECT

	public:
		WdgLogEntry(QWidget* parent);
		~WdgLogEntry(void);

	public slots:
		void add();
		void cancel();
		void reset();
		void setStartTime();
		void setEndTime();
		void setFreq();
		void setMode();
		void setCallsign(QString);

	signals:
		void tabNameChanged(QString, const WdgLogEntry*);
	};
}

#endif // LOGBOOK_WDGLOGENTRY_H
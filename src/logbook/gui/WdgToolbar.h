#ifndef LOGBOOK_WDGTOOLBAR_H
#define LOGBOOK_WDGTOOLBAR_H

#include "ui_WdgToolbar.h"

namespace logbook
{
	class WdgToolbar
		: public QWidget, public Ui::WdgToolbar
	{
		Q_OBJECT

	public:
		WdgToolbar(QWidget* parent);
		~WdgToolbar(void);
	};
}

#endif // LOGBOOK_WDGTOOLBAR_H
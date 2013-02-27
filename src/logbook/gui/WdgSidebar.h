#ifndef LOGBOOK_WDGSIDEBAR_H
#define LOGBOOK_WDGSIDEBAR_H

#include "ui_WdgSidebar.h"

namespace logbook
{
    class WdgSidebar
        : public QWidget, public Ui::WdgSidebar
	{
		Q_OBJECT

	public:
        WdgSidebar(QWidget* parent);
        ~WdgSidebar(void);
	};
}

#endif // LOGBOOK_WDGSIDEBAR_H

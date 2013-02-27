#ifndef DIGITAL_WDGSIDEBAR_H
#define DIGITAL_WDGSIDEBAR_H

#include "ui_WdgSidebar.h"

namespace digital
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

#endif // DIGITAL_WDGSIDEBAR_H

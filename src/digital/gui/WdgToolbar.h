#ifndef DIGITAL_WDGTOOLBAR_H
#define DIGITAL_WDGTOOLBAR_H

#include "ui_WdgToolbar.h"

namespace digital
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

#endif // DIGITAL_WDGTOOLBAR_H

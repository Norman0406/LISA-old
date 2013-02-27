#ifndef LISA_DLGABOUT_H
#define LISA_DLGABOUT_H

#include "ui_DlgAbout.h"

namespace lisa
{
	class DlgAbout
		: public QDialog, public Ui::DlgAbout
	{
		Q_OBJECT

	public:
		DlgAbout();
		~DlgAbout();
	};
}

#endif // LISA_DLGABOUT_H

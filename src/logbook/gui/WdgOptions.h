#ifndef LOGBOOK_WDGOPTIONS_H
#define LOGBOOK_WDGOPTIONS_H

#include <core/main/OptionsBase.h>
#include "ui_WdgOptions.h"

namespace logbook
{
	class WdgOptions
		: public core::OptionsBase, public Ui::WdgOptions
	{
		Q_OBJECT

	public:
		WdgOptions(core::PropertyList*, QWidget* parent);
		~WdgOptions(void);

		void apply();
		void cancel();
	};
}

#endif // LOGBOOK_WDGOPTIONS_H

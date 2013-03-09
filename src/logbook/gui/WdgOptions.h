#ifndef LOGBOOK_WDGOPTIONS_H
#define LOGBOOK_WDGOPTIONS_H

#include <core/main/OptionsBase.h>
#include "../main/LogbookModule.h"
#include "ui_WdgOptions.h"

namespace logbook
{
	class WdgOptions
		: public core::OptionsBase, public Ui::WdgOptions
	{
		Q_OBJECT

	public:
		WdgOptions(core::PropertyList*, const LogbookModule*, QWidget* parent);
		~WdgOptions(void);

		void apply();
		void cancel();
	};
}

#endif // LOGBOOK_WDGOPTIONS_H

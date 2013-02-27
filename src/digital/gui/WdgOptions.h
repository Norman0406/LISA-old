#ifndef DIGITAL_WDGOPTIONS_H
#define DIGITAL_WDGOPTIONS_H

#include <core/main/OptionsBase.h>
#include "ui_WdgOptions.h"

namespace digital
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

#endif // DIGITAL_WDGOPTIONS_H

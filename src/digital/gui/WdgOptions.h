#ifndef DIGITAL_WDGOPTIONS_H
#define DIGITAL_WDGOPTIONS_H

#include <core/main/OptionsBase.h>
#include "../main/DigitalModule.h"
#include "ui_WdgOptions.h"

namespace digital
{
	class WdgOptions
		: public core::OptionsBase, public Ui::WdgOptions
	{
		Q_OBJECT

	public:
		WdgOptions(core::PropertyList*, const DigitalModule*, QWidget* parent);
		~WdgOptions(void);
		
		void apply();
		void cancel();
	};
}

#endif // DIGITAL_WDGOPTIONS_H

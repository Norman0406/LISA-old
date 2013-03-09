#include "WdgOptions.h"

namespace digital
{
	WdgOptions::WdgOptions(core::PropertyList* properties, const DigitalModule* module, QWidget* parent)
		: OptionsBase(properties, module, parent)
	{
		setupUi(this);
	}

	WdgOptions::~WdgOptions(void)
	{
	}
	
	void WdgOptions::apply()
	{
	}

	void WdgOptions::cancel()
	{
	}
}

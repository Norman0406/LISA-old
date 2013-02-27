#include "WdgOptions.h"

namespace logbook
{
	WdgOptions::WdgOptions(core::PropertyList* properties, QWidget* parent)
		: OptionsBase(properties, parent)
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

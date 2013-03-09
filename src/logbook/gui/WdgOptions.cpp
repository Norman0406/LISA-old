#include "WdgOptions.h"

namespace logbook
{
	WdgOptions::WdgOptions(core::PropertyList* properties, const LogbookModule* module, QWidget* parent)
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

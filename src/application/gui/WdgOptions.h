#ifndef LISA_WDGOPTIONS_H
#define LISA_WDGOPTIONS_H

#include <core/main/OptionsBase.h>
#include <core/main/Property.h>
#include "ui_WdgOptions.h"

namespace lisa
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
		
	private:
		void initStyle();

	private:
		core::Property<QString>* m_propStyle;
	};
}

#endif // LISA_WDGOPTIONS_H

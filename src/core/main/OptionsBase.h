#ifndef CORE_OPTIONSBASE_H
#define CORE_OPTIONSBASE_H

#include <QtWidgets/QtWidgets>

namespace core
{
	class PropertyList;

	// base class for a widget inside the options dialog
	class OptionsBase
		: public QWidget
	{
		Q_OBJECT

	public:
		virtual ~OptionsBase();

		virtual void apply() = 0;
		virtual void cancel() = 0;

	protected:
		OptionsBase(PropertyList*, QWidget* parent);

		PropertyList* m_properties;
	};

	// a default options widgets
	class WdgOptionsDefault
		: public OptionsBase
	{
	public:
		WdgOptionsDefault(QWidget*);
		~WdgOptionsDefault();
		
		void apply();
		void cancel();
	};
}

#endif // CORE_OPTIONSBASE_H

#include "OptionsBase.h"
#include "PropertyList.h"

namespace core
{
	OptionsBase::OptionsBase(PropertyList* properties, QWidget* parent)
		: QWidget(parent), m_properties(properties)
	{
	}

	OptionsBase::~OptionsBase()
	{
	}
	
	WdgOptionsDefault::WdgOptionsDefault(QWidget* parent)
		: OptionsBase(0, parent)
	{
		QLabel* label = new QLabel("This module does not have any options.", this);
		label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		QVBoxLayout* layout = new QVBoxLayout(this);
		layout->addWidget(label);
		setLayout(layout);
		setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	}

	WdgOptionsDefault::~WdgOptionsDefault()
	{
	}

	void WdgOptionsDefault::apply()
	{
	}

	void WdgOptionsDefault::cancel()
	{
	}
}

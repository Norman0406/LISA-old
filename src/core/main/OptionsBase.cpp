#include "OptionsBase.h"
#include "PropertyList.h"
#include "Module.h"

namespace core
{
	OptionsBase::OptionsBase(PropertyList* properties, const Module* module, QWidget* parent)
		: QWidget(parent), m_properties(properties), m_module(module)
	{
	}

	OptionsBase::~OptionsBase()
	{
	}
	
	const Module* OptionsBase::getModule() const
	{
		return m_module;
	}
	
	WdgOptionsDefault::WdgOptionsDefault(const Module* module, QWidget* parent)
		: OptionsBase(0, module, parent)
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

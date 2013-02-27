#include "PropertyBase.h"

namespace core
{
	PropertyBase::PropertyBase(QString name)
		: m_name(name)
	{
	}
	
	PropertyBase::PropertyBase(const PropertyBase& other)
	{
		m_name = other.getNameStr();
	}
	
	PropertyBase::~PropertyBase()
	{
	}

	QString PropertyBase::getNameStr() const
	{
		return m_name;
	}
}

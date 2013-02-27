#include "QSOFieldBase.h"

namespace logbook
{
	QSOFieldBase::QSOFieldBase(QString name)
		: m_name(name)
	{
	}

	QSOFieldBase::~QSOFieldBase()
	{
	}
	 
	QString QSOFieldBase::getNameStr() const
	{
		return m_name;
	}
}

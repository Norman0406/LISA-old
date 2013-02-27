#ifndef LOGBOOK_QSOFIELD_H
#define LOGBOOK_QSOFIELD_H

#include "QSOFieldBase.h"

#include <QtCore/QDate>
#include <QtCore/QTime>

namespace logbook
{
	template <typename T>
	class QSOField
		: public QSOFieldBase
	{
	public:
		QSOField(QString);
		~QSOField();
		
		QString getTypeStr() const;
		QString getValueStr() const;
	};

	// template implementation
	template <typename T>
	QSOField<T>::QSOField(QString name)
		: QSOFieldBase(name)
	{
	}
	
	template <typename T>
	QSOField<T>::~QSOField()
	{
	}
	
	template <typename T>
	QString QSOField<T>::getTypeStr() const
	{
		return "";
	}
	
	template <typename T>
	QString QSOField<T>::getValueStr() const
	{
		return "";
	}
}

#endif // LOGBOOK_QSOFIELD_H
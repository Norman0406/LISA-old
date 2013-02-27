#include "QSOEntry.h"
#include "QSOField.h"

namespace logbook
{
	QSOEntry::QSOEntry()
	{
		initStandardFields();
	}

	QSOEntry::~QSOEntry()
	{
		clear();
	}

	void QSOEntry::clear()
	{
		clear(m_standardFields);
		clear(m_additionalFields);
	}
	
	void QSOEntry::clear(QVector<QSOFieldBase*>& fields)
	{
		for (int i = 0; i < fields.size(); i++)
			delete fields[i];
		fields.clear();
	}

	void QSOEntry::addField(const QSOFieldBase& field)
	{
		addField(field, m_additionalFields);
	}

	void QSOEntry::addField(const QSOFieldBase& field, QVector<QSOFieldBase*>& fields)
	{
		Q_UNUSED(field);
		Q_UNUSED(fields);
	}

	void QSOEntry::initStandardFields()
	{
		addField(QSOField<QDate>("Date"));
		addField(QSOField<QTime>("Start"));
		addField(QSOField<QTime>("End"));
		addField(QSOField<QString>("Callsign"));
		addField(QSOField<int>("RSTsent"));
		addField(QSOField<int>("RSTrcvd"));
		addField(QSOField<float>("Freq"));
		addField(QSOField<QString>("Mode"));
		addField(QSOField<QString>("Country"));
		addField(QSOField<QString>("Locator"));
		addField(QSOField<QString>("Comment"));	
	}
}

#ifndef LOGBOOK_QSOENTRY_H
#define LOGBOOK_QSOENTRY_H

#include "QSOFieldBase.h"
#include <QtCore/QVector>

namespace logbook
{
	class QSOEntry
	{
	public:
		QSOEntry();
		~QSOEntry();

		void clear();
		void addField(const QSOFieldBase&);

	private:
		void initStandardFields();
		void clear(QVector<QSOFieldBase*>&);
		void addField(const QSOFieldBase&, QVector<QSOFieldBase*>&);

		QVector<QSOFieldBase*> m_standardFields;
		QVector<QSOFieldBase*> m_additionalFields;

		//QSOLayout	m_layout;
	};
}

#endif // LOGBOOK_QSOENTRY_H
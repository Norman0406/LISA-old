#ifndef LOGBOOK_QSOFIELDBASE_H
#define LOGBOOK_QSOFIELDBASE_H

#include <QtCore/QString>

namespace logbook
{
	class QSOFieldBase
	{
	public:
		virtual ~QSOFieldBase();

		QString getNameStr() const;
		virtual QString getTypeStr() const = 0;
		virtual QString getValueStr() const = 0;

	protected:
		QSOFieldBase(QString);

	private:
		const QString m_name;
	};
}

#endif // LOGBOOK_QSOFIELDBASE_H
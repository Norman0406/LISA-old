#ifndef CORE_PROPERTYBASE_H
#define CORE_PROPERTYBASE_H

#include <QtCore/QString>
#include <QtCore/QXmlStreamReader>
#include <QtCore/QXmlStreamWriter>

namespace core
{
	class PropertyBase
	{
	public:
		virtual ~PropertyBase();

		QString getNameStr() const;
		virtual QString getTypeStr() const = 0;
		virtual QString getValueStr() const = 0;
		virtual QString getDefaultValueStr() const = 0;
		virtual bool setValueFromStr(QString) = 0;
		virtual void setToDefault() = 0;
		
	protected:
		PropertyBase(const PropertyBase&);
		PropertyBase(QString);

	private:
		QString m_name;
	};
}

#endif // CORE_PROPERTYBASE_H
#ifndef CORE_PROPERTYLIST_H
#define CORE_PROPERTYLIST_H

#include <sstream>
#include <QtCore/QSettings>
#include "Property.h"

namespace core
{	
	// overloaded stringstream operators for non-standard types
	std::stringstream& operator<<(std::stringstream& sstr, const QString& val);
	std::stringstream& operator>>(std::stringstream& sstr, QString& val);

	class PropertyList
	{
	public:
		PropertyList();
		~PropertyList();
		
		template <typename T>
		bool addProperty(const Property<T>&);

		template <typename T>
		Property<T>* getProperty(const QString&);

		PropertyBase* getPropertyBase(const QString&) const;

		bool loadFromFile(QString filename, QString moduleName);
		bool saveToFile(QString filename, QString moduleName);

	private:
		bool readDocument(QXmlStreamReader&, const QString&);
		bool writeDocument(QXmlStreamWriter&, const QString&) const;

		QVector<PropertyBase*> m_properties;	// properties are owned
	};

	template <typename T>
	bool PropertyList::addProperty(const Property<T>& prop)
	{
		// check if property already exists
		for (int i = 0; i < m_properties.size(); i++) {
			if (m_properties[i]->getNameStr() == prop.getNameStr())
				return false;
		}

		m_properties.push_back(new Property<T>(prop));

		return true;
	}
	
	template <typename T>
	Property<T>* PropertyList::getProperty(const QString& name)
	{
		PropertyBase* prop = getPropertyBase(name);

		if (prop->getTypeStr() == PropertyTraits<T>::getTypeStr())
			return dynamic_cast<Property<T>*>(prop);

		return 0;
	}
}

#endif // CORE_PROPERTYLIST_H
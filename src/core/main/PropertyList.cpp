#include "PropertyList.h"
#include <QtCore/QStringList>
#include <QtCore/QFile>
#include <QtCore/QDebug>

namespace core
{
	// overloaded stringstream operators for non-standard types
	std::stringstream& operator<<(std::stringstream& sstr, const QString& val)
	{
		sstr << val.toStdString();
		return sstr;
	}

	std::stringstream& operator>>(std::stringstream& sstr, QString& val)
	{
		std::string str;
		sstr >> str;
		val = val.fromStdString(str);
		return sstr;
	}

	PropertyList::PropertyList()
	{
	}

	PropertyList::~PropertyList()
	{
		for (int i = 0; i < m_properties.size(); i++)
			delete m_properties[i];
		m_properties.clear();
	}
	
	PropertyBase* PropertyList::getPropertyBase(const QString& name) const
	{
		for (int i = 0; i < m_properties.size(); i++) {
			PropertyBase* prop = m_properties[i];
			if (prop->getNameStr() == name)
				return prop;
		}

		return 0;
	}

	bool PropertyList::loadFromFile(QString filename, QString moduleName)
	{
		QFile file(filename);
		if (file.open(QFile::ReadOnly)) {
			QXmlStreamReader xmlReader(&file);
			return readDocument(xmlReader, moduleName);
		}

		return true;
	}

	bool PropertyList::saveToFile(QString filename, QString moduleName)
	{
		QFile file(filename);
		if (file.open(QFile::WriteOnly)) {
			QXmlStreamWriter xmlWriter(&file);
			return writeDocument(xmlWriter, moduleName);
		}

		return false;
	}
	
	bool PropertyList::readDocument(QXmlStreamReader& reader, const QString& moduleName)
	{
		bool foundStart = false;

		while (!reader.atEnd()) {
			QXmlStreamReader::TokenType token = reader.readNext();

			// check start element
			if (token == QXmlStreamReader::StartElement && reader.name() == "PropertyList") {
				QXmlStreamAttributes attrList = reader.attributes();

				// check if there is the right attribute
				for (int i = 0; i < attrList.size(); i++) {
					const QXmlStreamAttribute& attr = attrList[i];
					
					if (attr.name() == "ModuleName" && attr.value() == moduleName) {
						foundStart = true;
						break;
					}
				}

				if (foundStart)
					continue;
			}
			else if (token == QXmlStreamReader::StartElement && foundStart) {

				// get property node
				if (reader.name() == "Property") {

					// get attributes list
					QXmlStreamAttributes attrList = reader.attributes();
					const QXmlStreamAttribute* attrName = 0;
					const QXmlStreamAttribute* attrType = 0;

					// find name and type attributes
					for (int i = 0; i < attrList.size(); i++) {
						QXmlStreamAttribute attr = attrList[i];
						
						// find type attribute
						if (attr.name() == "Name")
							attrName = &attrList[i];
						else if (attr.name() == "Type")
							attrType = &attrList[i];
					}

					if (!attrName || !attrType)
						continue;

					// find matching property
					for (int i = 0; i < m_properties.size(); i++) {
						PropertyBase* prop = m_properties[i];
						
						if (prop->getNameStr() == attrName->value().toString()) {
							// we found a property, check the type
							if (prop->getTypeStr() == attrType->value().toString()) {
								// everything is fine, set the property value
								
								QString content = reader.readElementText();
								prop->setValueFromStr(content);
								
								break;
							}
						}
					}

				}
			}
		}

		return true;
	}

	bool PropertyList::writeDocument(QXmlStreamWriter& writer, const QString& moduleName) const
	{
		writer.setAutoFormatting(true);
		writer.writeStartDocument();
		writer.writeStartElement("PropertyList");
		writer.writeAttribute("ModuleName", moduleName);

		for (int i = 0; i < m_properties.size(); i++) {
			const PropertyBase* prop = m_properties[i];
			
			writer.writeStartElement("Property");
		
			writer.writeAttribute("Name", prop->getNameStr());
			writer.writeAttribute("Type", prop->getTypeStr());
			writer.writeCharacters(prop->getValueStr());

			writer.writeEndElement();
		}

		writer.writeEndElement();
		writer.writeEndDocument();

		return true;
	}
}

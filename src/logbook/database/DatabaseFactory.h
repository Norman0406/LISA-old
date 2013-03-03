#ifndef LOGBOOK_DATABASEFACTORY_H
#define LOGBOOK_DATABASEFACTORY_H

#include <core/common/Factory.h>
#include "DatabaseXML.h"

template <>
QStringList Factory<logbook::Database>::getKeys()
{
	QStringList keys;

	// push all available types here
	keys.push_back("xml");

	return QStringList();
}

template <>
logbook::Database* Factory<logbook::Database>::createByKey(QString key)
{
	// create types by key
	if (key == "xml")
		return new logbook::DatabaseXML();

	return 0;
}

#endif // LOGBOOK_DATABASEFACTORY_H

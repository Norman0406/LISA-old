#ifndef LOGBOOK_DATABASEXML_H
#define LOGBOOK_DATABASEXML_H

#include "Database.h"

namespace logbook
{
	class DatabaseXML
		: public Database
	{
	public:
		DatabaseXML();
		~DatabaseXML();
	};
}

#endif // LOGBOOK_DATABASEXML_H
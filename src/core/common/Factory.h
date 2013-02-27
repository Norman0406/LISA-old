#ifndef CORE_FACTORY_H
#define CORE_FACTORY_H

#include <QtCore/QString>
#include <QtCore/QStringList>

// no namespace to allow generic specialization

template <typename T>
class Factory
{
public:
	Factory();	// not implemented
	~Factory();	// not implemented
		
	// implement these functions in your specialized factory
	static QStringList getKeys();
	static T* createByKey(QString);
};

#endif // CORE_FACTORY_H
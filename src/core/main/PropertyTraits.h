#ifndef CORE_PROPERTYTRAITS_H
#define CORE_PROPERTYTRAITS_H

namespace core
{
	template <typename T>
	struct PropertyTraits
	{
	};

#define MAKE_PROPERTY_TRAIT(type) \
	template <> \
	struct PropertyTraits<type> \
	{ \
		static const char* getTypeStr() { \
			return #type; \
		} \
	}; \
	
	MAKE_PROPERTY_TRAIT(char);
	MAKE_PROPERTY_TRAIT(bool);
	MAKE_PROPERTY_TRAIT(int);
	MAKE_PROPERTY_TRAIT(float);
	MAKE_PROPERTY_TRAIT(double);
	MAKE_PROPERTY_TRAIT(QString);
}

#endif // CORE_PROPERTYTRAITS_H
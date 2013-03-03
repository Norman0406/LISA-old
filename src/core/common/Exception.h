#ifndef CORE_EXCEPTION_H
#define CORE_EXCEPTION_H

#include <exception>
#include <QtCore/QString>

namespace core
{
	// exception macro
#define EXCEPTION(ExClass, msg) ExClass(this->getModuleName(), Q_FUNC_INFO, msg)

	class Exception
		: public std::exception
	{
	public:
		Exception(QString module, QString funcInfo, QString message);
        virtual ~Exception() throw();

		const char* what() const throw();
		void show();

	private:
		QString m_module;
		QString m_funcInfo;
		QString m_message;
	};

	/*class SystemException;
	class ModuleException;
	class XMLException;
	class QtException;*/
}

#endif // CORE_EXCEPTION_H

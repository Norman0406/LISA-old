#include "Exception.h"
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QApplication>
#include <QtCore/QDebug>

namespace core
{
	Exception::Exception(QString module, QString funcInfo, QString message)
		: m_module(module), m_funcInfo(funcInfo), m_message(message)
	{
	}

    Exception::~Exception() throw()
	{
	}

	const char* Exception::what() const throw()
	{
		return m_message.toStdString().c_str();
	}

	void Exception::show()
	{
		QString msg = "Module: " + m_module + "\nFunction: " + m_funcInfo + "\n\nMessage: \"" +
			m_message + "\"";

		qCritical() << m_message;

		QMessageBox::critical(0, "Exception", msg, QMessageBox::Ok);
	}
}

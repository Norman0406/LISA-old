#include "Logging.h"
#include <QtCore/qlogging.h>

namespace core
{
	Logging* Logging::m_instance = 0;

	Logging::Logging()
	{
		qRegisterMetaType<LoggingEntry>("LoggingEntry");
		qInstallMessageHandler(Logging::messageHandler);
	}

	Logging::~Logging()
	{
		qDebug() << "Log closed at " << QDateTime::currentDateTime().toString();
		qInstallMessageHandler(0);
	}

	Logging* Logging::instance()
	{
		if (!m_instance) {
			m_instance = new Logging();
			qDebug() << "Log started at " << qPrintable(QDateTime::currentDateTime().toString());
		}

		return Logging::m_instance;
	}

	void Logging::log(QtMsgType type, const QMessageLogContext& context, const QString& msg)
	{
		QString line;
		QColor col = Qt::black;
		
		bool verbose = true;

		QString typeStr;
		switch (type) {
		case QtDebugMsg:
			typeStr = "Info";	// let's call it "Info"
			verbose = false;
			col = Qt::black;
			break;
		case QtWarningMsg:
			typeStr = "Warning";
			col = Qt::darkYellow;
			break;
		case QtCriticalMsg:	// == QtSystemMsg
			typeStr = "Critical";
			col = Qt::darkRed;
			break;
		case QtFatalMsg:
			typeStr = "Fatal";
			col = Qt::darkRed;
			break;
		default:
			typeStr = "Unknown";
			col = Qt::black;
			break;
		}

		// get detailed information
		QString file = context.file;
		QString func = context.function;
		int lineNr = context.line;
		QString verboseInfo = "\"" + file + "\"" + " : " + func + " : " + QString::number(lineNr);
		
		// construct header
		QString now = QDateTime::currentDateTime().toString("hh:mm:ss");
		QString front = "[" + now + " (" + typeStr + ")] ";
		
		line = front + msg;

		if (verbose)
			line += " (" + verboseInfo + ")";

		// remove double whitespaces
		line = line.simplified();
						
		LoggingEntry entry;
		entry.m_type = type;
		entry.m_line = line;
		entry.m_textCol = col;

		m_loggingEntries.push_back(entry);

		// output to debugging window (visual studio specific)
#ifdef _MSC_VER
		QString dbgLine = line + "\n";
		OutputDebugString(dbgLine.toStdWString().c_str());
#endif
		
		emit newLoggingEntry(entry);
	}
	
	const QVector<LoggingEntry>& Logging::getEntries() const
	{
		return m_loggingEntries;
	}
	
	void Logging::messageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg)
	{
		Logging::instance()->log(type, context, msg);
	}
}

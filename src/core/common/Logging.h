#ifndef CORE_LOGGING_H
#define CORE_LOGGING_H

#include <QtCore/QtMessageHandler>
#include <QtCore/QVector>
#include <QtGui/QColor>

namespace core
{
	struct LoggingEntry
	{
		QString m_line;
		QColor m_textCol;
		QtMsgType m_type;
	};

	class Logging
		: public QObject
	{
		Q_OBJECT

	public:
		virtual ~Logging();

		static Logging* instance();
		const QVector<LoggingEntry>& getEntries() const;
		static void messageHandler(QtMsgType, const QMessageLogContext&, const QString&);

	signals:
		void newLoggingEntry(const LoggingEntry&);
		
	protected:
		Logging();

	private:
		void log(QtMsgType, const QMessageLogContext&, const QString&);

		static Logging* m_instance;
		QVector<LoggingEntry> m_loggingEntries;
	};
}

#endif // CORE_LOGGING_H

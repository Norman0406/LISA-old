#ifndef LISA_SYSTEM_H
#define LISA_SYSTEM_H

#include <QtWidgets/QApplication>
#include <QtCore/QVector>
#include <core/common/Logging.h>

namespace core
{
	class Module;
}

namespace lisa
{
	class LISAModule;

	// singleton
	class System
		: public QObject
	{
		Q_OBJECT

	public:
		~System(void);

		static System* init(int argc, char *argv[]);

		int run();
		
	private slots:
		void msgRegister(QString);
		void msgSend(QString, const QVariant&);
		void enableModule(const QString&, bool);
		void fillDetectedModule(QVector<QString>&);
		void moduleLoaded(const QString&, bool&);
		
	private:
		System(int argc, char *argv[]);

		bool init();

		bool removeModule(core::Module*);
		bool initModule(core::Module*);
		bool initModules();
		void applyProperties();
		void detectModules();
		void loadModules();
		core::Module* loadModule(const QString&);
		bool isModuleLoaded(const QString&);
		
		void loadState();
		void saveState();

		static System*		m_instance;
		QApplication		m_application;
		LISAModule*			m_mainModule;
		core::Logging*		m_logging;

		QMap<QString, QString> m_detectedModules;

		QVector<core::Module*>	m_modules;
        QMap<QString, QPair<QByteArray, QByteArray> > m_stateInfo;
        QMap<QString, QVector<core::Module*> > m_registeredMessages;
	};
}

#endif // LISA_SYSTEM_H

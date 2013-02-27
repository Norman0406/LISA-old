#ifndef LISA_LISAMODULE_H
#define LISA_LISAMODULE_H

#include <core/common/Logging.h>
#include <core/main/Module.h>
#include "../gui/MainWindow.h"

namespace lisa
{
	class LISAModule
		: public core::Module
	{
		Q_OBJECT

	public:
		LISAModule();
		~LISAModule(void);
		
		QString	getModuleName() const;
		QString getDisplayName() const;
		bool isInit() const;
		
		bool createWindow();
		
		MainWindow* getWindow();
		core::OptionsBase* getOptionsWdg(QWidget*);
		
		QByteArray saveGeometry();
		bool restoreGeometry(const QByteArray&);
		QByteArray saveState();
		bool restoreState(const QByteArray&);

	public slots:
		void createOptionWidgets(QMap<QString, core::OptionsBase*>&, QWidget*);

	protected:
		bool iInit(QWidget*);

	private:
		MainWindow* m_mainWindow;
	};
}

#endif // LISA_LISAMODULE_H

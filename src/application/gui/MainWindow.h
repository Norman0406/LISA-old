#ifndef LISA_MAINWINDOW_H
#define LISA_MAINWINDOW_H

#include <core/main/Module.h>
#include <core/common/Logging.h>
#include "ui_MainWindow.h"

namespace lisa
{
	class WdgLogging;
	class System;

	class MainWindow
		: public QMainWindow, public Ui::MainWindow
	{
		Q_OBJECT

	public:
		MainWindow(QWidget* parent = 0);
		~MainWindow(void);

	public slots:
		void showAboutDlg();
		void showOptionsDlg();
		void newLoggingEntry(const core::LoggingEntry&);
		void addModuleWidget(core::Module::WidgetType, const QString&, QWidget*);
		
	signals:
        void createOptionWidgets(QVector<QPair<QString, core::OptionsBase*> >&, QWidget*);
		
	protected:
		bool iInit();

	private:
		WdgLogging* m_wdgLogging;

	};
}

#endif // LISA_MAINWINDOW_H

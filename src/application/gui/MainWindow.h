#ifndef LISA_MAINWINDOW_H
#define LISA_MAINWINDOW_H

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
		MainWindow(System*, QWidget* parent = 0);
		~MainWindow(void);
				
		void addMenu(QMenu*);
		void addMainWidget(QWidget*, QString);
		void addToolbarWidget(QWidget*, QString);
		
	public slots:
		void showAboutDlg();
		void showOptionsDlg();
		void newLoggingEntry(const core::LoggingEntry&);
		
	protected:
		bool iInit();

	private:
		System*			m_system;
		WdgLogging*		m_wdgLogging;

	};
}

#endif // LISA_MAINWINDOW_H

#include "DlgAbout.h"
#include "DlgOptions.h"
#include "WdgLogging.h"
#include "WdgOptions.h"
#include "MainWindow.h"
#include "../main/System.h"
#include <QtCore/QFile>

namespace lisa
{
	MainWindow::MainWindow(System* system, QWidget* parent)
		: QMainWindow(parent),
		m_wdgLogging(0), m_system(system)
	{
		setupUi(this);
		
		// add toolbar toggles to "View" menu
		QList<QMenu*> entries = appMenuBar->findChildren<QMenu*>();
		for (QList<QMenu*>::const_iterator it = entries.begin(); it != entries.end(); it++) {
			QMenu* curMenu = *it;
			if (curMenu->title() == "View") {
				curMenu->addAction(appToolBar->toggleViewAction());
				curMenu->addAction(appLogging->toggleViewAction());
				curMenu->addSeparator();
				break;
			}
		}
		
		// add logging widget to dock widget
		m_wdgLogging = new WdgLogging(this);
		appLoggingLayout->addWidget(m_wdgLogging);
	}
	
	MainWindow::~MainWindow(void)
	{
	}
	
	void MainWindow::addMenu(QMenu* menu)
	{
		menu->setTearOffEnabled(true);
		
		bool found = false;
		
		// insert before "Help" menu
		QList<QMenu*> entries = appMenuBar->findChildren<QMenu*>();
		for (QList<QMenu*>::const_iterator it = entries.begin(); it != entries.end(); it++) {
			const QMenu* curMenu = *it;
			if (curMenu->title() == "Help") {
				appMenuBar->insertMenu(curMenu->menuAction(), menu);
				found = true;
				break;
			}			
		}

		if (!found)
			appMenuBar->addMenu(menu);
	}

	void MainWindow::addMainWidget(QWidget* widget, QString tabName)
	{
		appMainWidgets->addTab(widget, tabName);
	}

	void MainWindow::addToolbarWidget(QWidget* widget, QString tabName)
	{
		appToolbarWidgets->addTab(widget, tabName);
	}

	void MainWindow::showAboutDlg()
	{
		DlgAbout dlg;
		dlg.setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint | Qt::WindowTitleHint | Qt::WindowStaysOnTopHint);
		dlg.exec();	// shows a modal dialog
	}
	
	void MainWindow::showOptionsDlg()
	{
		DlgOptions dlg(m_system->getModules());
		dlg.setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint | Qt::WindowTitleHint | Qt::WindowStaysOnTopHint);
		dlg.exec();
	}
	
	void MainWindow::newLoggingEntry(const core::LoggingEntry& entry)
	{
		if (m_wdgLogging)
			m_wdgLogging->addLogEntry(entry);
	}
}

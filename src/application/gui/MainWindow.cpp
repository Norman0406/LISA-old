#include "DlgAbout.h"
#include "DlgOptions.h"
#include "WdgLogging.h"
#include "WdgOptions.h"
#include "MainWindow.h"
#include "../main/System.h"
#include <QtCore/QFile>

namespace lisa
{
	MainWindow::MainWindow(QWidget* parent)
		: QMainWindow(parent), m_wdgLogging(0)
	{
		setupUi(this);

		appSidebarWidgets->removeItem(0);
		
		// add toolbar toggles to "View" menu
		QList<QMenu*> entries = appMenuBar->findChildren<QMenu*>();
		for (QList<QMenu*>::const_iterator it = entries.begin(); it != entries.end(); it++) {
			QMenu* curMenu = *it;
			if (curMenu->title() == "View") {
				curMenu->addAction(appToolbar->toggleViewAction());
				curMenu->addAction(appSidebar->toggleViewAction());
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

	void MainWindow::addModuleWidget(core::Module::WidgetType type, const QString& text, QWidget* widget)
	{
		QString typeStr = "unknown";
		switch (type) {
		case core::Module::WT_MAIN:
			typeStr = "WT_MAIN";
			appMainWidgets->addTab(widget, text);
			break;
		case core::Module::WT_TOOLBAR:
			typeStr = "WT_TOOLBAR";
			appToolbarWidgets->addTab(widget, text);
			break;
		case core::Module::WT_SIDEBAR:
			typeStr = "WT_SIDEBAR";
			appSidebarWidgets->addItem(widget, text);
			break;
		}

		qDebug() << "added widget with type " << typeStr << " and text " << text;
	}
	
	void MainWindow::showAboutDlg()
	{
		DlgAbout dlg;
		dlg.setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint | Qt::WindowTitleHint | Qt::WindowStaysOnTopHint);
		dlg.exec();	// shows a modal dialog
	}
	
	void MainWindow::showOptionsDlg()
	{
		DlgOptions dlg;

		// create options widget for dialog to create child widgets
		connect(&dlg, &DlgOptions::createOptionWidgets, this, &MainWindow::createOptionWidgets);
		connect(&dlg, &DlgOptions::enableModule, this, &MainWindow::enableModule);

		dlg.init();
		dlg.setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint | Qt::WindowTitleHint | Qt::WindowStaysOnTopHint);
		dlg.exec();
	}
	
	void MainWindow::newLoggingEntry(const core::LoggingEntry& entry)
	{
		if (m_wdgLogging)
			m_wdgLogging->addLogEntry(entry);
	}
}

#include "WdgLogEntry.h"
#include "WdgLogbook.h"

namespace logbook
{
	WdgLogbook::WdgLogbook(QWidget* parent)
		: QMainWindow(parent),
		m_tabBarCloseButton(0)
	{
		setupUi(this);
		
		// add a default log entry
		addNewEntry(0);
		
		editButton->setChecked(false);
		showLogEntries(editButton->isChecked());

		// init database layout
		initDatabaseLayout();
	}

	WdgLogbook::~WdgLogbook(void)
	{
	}
	
	void WdgLogbook::initDatabaseLayout()
	{
		QTableView* table = tableView;

		QStandardItemModel* model = new QStandardItemModel(this);
		model->setHorizontalHeaderItem(0, new QStandardItem("Date"));
		model->setHorizontalHeaderItem(1, new QStandardItem("Start"));
		model->setHorizontalHeaderItem(2, new QStandardItem("Callsign"));
		model->setHorizontalHeaderItem(3, new QStandardItem("Sent"));
		model->setHorizontalHeaderItem(4, new QStandardItem("Rcvd"));
		model->setHorizontalHeaderItem(5, new QStandardItem("Freq"));
		model->setHorizontalHeaderItem(6, new QStandardItem("Band"));
		model->setHorizontalHeaderItem(7, new QStandardItem("Mode"));
		model->setHorizontalHeaderItem(8, new QStandardItem("Name"));
		model->setHorizontalHeaderItem(9, new QStandardItem("Country"));
		model->setHorizontalHeaderItem(10, new QStandardItem("Locator"));
		model->setHorizontalHeaderItem(11, new QStandardItem("Distance"));
		model->setHorizontalHeaderItem(12, new QStandardItem("Comment"));
		
		table->setModel(model);
	}
		
	void WdgLogbook::addNewEntry(int index)
	{
		// create a new entry, if "+" tab is pressed
		if (index == tabWidget->count() - 1) {
			int position = tabWidget->count() - 1;
			WdgLogEntry* entry = new WdgLogEntry(this);

			// connect
			QObject::connect(entry, &WdgLogEntry::tabNameChanged, this, &WdgLogbook::changeTabName);

			tabWidget->insertTab(position, entry, "New entry");
			tabWidget->setCurrentIndex(position);

			// remove close button on first tab
			if (tabWidget->count() <= 2) {
				m_tabBarCloseButton = tabWidget->tabBar()->tabButton(0, QTabBar::RightSide);
				tabWidget->tabBar()->setTabButton(0, QTabBar::RightSide, 0);
			}
			
			//tabWidget->tabBar()->tabButton(position, QTabBar::RightSide)->setFixedSize(12, 12);

			// remove close button on "+" tab
			tabWidget->tabBar()->setTabButton(position + 1, QTabBar::RightSide, 0);
					
			// restore close button on first tab
			if (tabWidget->count() > 2 && m_tabBarCloseButton) {
				tabWidget->tabBar()->setTabButton(0, QTabBar::RightSide, m_tabBarCloseButton);
				m_tabBarCloseButton = 0;
			}
		}
	}

	void WdgLogbook::closeLogEntry(int index)
	{
		// find log entry and cancel changes
		QList<WdgLogEntry*> entries = tabWidget->findChildren<WdgLogEntry*>();
		for (int i = 0; i < entries.size(); i++) {
			if (i == index) {
				WdgLogEntry* entry = entries[i];
				entry->cancel();
				break;
			}
		}
		
		// select appropriate tab
		if (index == tabWidget->count() - 2)
			tabWidget->setCurrentIndex(index - 1);
		else if (tabWidget->count() > 1)
			tabWidget->setCurrentIndex(index);
		else if (tabWidget->count() <= 1)
			tabWidget->setCurrentIndex(0);
		
		// remove tab
		tabWidget->removeTab(index);
		
		// remove close button on first tab
		if (tabWidget->count() <= 2) {
			m_tabBarCloseButton = tabWidget->tabBar()->tabButton(0, QTabBar::RightSide);
			tabWidget->tabBar()->setTabButton(0, QTabBar::RightSide, 0);
		}
	}

	void WdgLogbook::showLogEntries(bool checked)
	{
		if (checked)
			tabWidget->setVisible(true);
		else
			tabWidget->setVisible(false);
	}
	
	void WdgLogbook::changeTabName(QString name, const WdgLogEntry* entry)
	{
		// UNDONE: does not work always with multiple tabs
		QList<WdgLogEntry*> entries = tabWidget->findChildren<WdgLogEntry*>();
		for (int i = 0; i < entries.size(); i++) {
			WdgLogEntry* curEntry = entries[i];
			if (curEntry == entry) {
				tabWidget->setTabText(i, name);
				break;
			}
		}
	}
}

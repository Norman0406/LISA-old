#include "DlgOptions.h"
#include <core/main/OptionsBase.h>
#include <core/main/Module.h>
#include "MainWindow.h"

namespace lisa
{
	DlgOptions::DlgOptions()
		: QDialog(0)
	{
		setupUi(this);
	}

	DlgOptions::~DlgOptions()
	{
	}

	void DlgOptions::init()
	{
		m_options.clear();
		createOptionWidgets(m_options, this);

		for (int i = 0; i < m_options.size(); i++) {
			QString text = m_options[i].first;
			core::OptionsBase* widget = m_options[i].second;
			
			// add widget to stacked widget
			stackedWidget->addWidget(widget);

			QListWidgetItem* item = new QListWidgetItem(optModules);
			item->setText(text);

			optModules->addItem(item);
		}
		optModules->setCurrentRow(0);
	}
	
	void DlgOptions::entryChanged(QString text)
	{
		core::OptionsBase* widget = 0;
		for (int i = 0; i < m_options.size(); i++) {
			QString val = m_options[i].first;
			if (val == text) {
				widget = m_options[i].second;
				break;
			}
		}

		if (!widget) {
			qWarning() << "did not find entry " << text;
			return;
		}
		
		optName->setText(text);
		stackedWidget->setCurrentWidget(widget);
	}

	/*void DlgOptions::deactivate(QListWidgetItem* item)
	{
		// TODO: don't enable deactivation of main application module
		
		core::OptionsBase* widget = 0;
		for (int i = 0; i < m_options.size(); i++) {
			QString val = m_options[i].first;
			if (val == item->text()) {
				widget = m_options[i].second;
				break;
			}
		}

		if (!widget) {
			qWarning() << "did not find entry " << item->text();
			return;
		}

		if (item && this->isVisible()) {
			if (item->checkState() == Qt::Checked) {
				item->setTextColor(Qt::black);
				emit enableModule(widget->getModule()->getModuleName(), true);
			}
			else {
				item->setTextColor(Qt::darkGray);
				emit enableModule(widget->getModule()->getModuleName(), false);
			}
		}
	}*/
	
	void DlgOptions::accept()
	{
		apply();
		QDialog::accept();
	}
	
	void DlgOptions::apply()
	{
		for (int i = 0; i < m_options.size(); i++)
			m_options[i].second->apply();
	}

	void DlgOptions::reject()
	{
		for (int i = 0; i < m_options.size(); i++)
			m_options[i].second->cancel();
		QDialog::reject();
	}
}

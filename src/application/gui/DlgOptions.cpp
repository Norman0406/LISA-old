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

		for (QMap<QString, core::OptionsBase*>::const_iterator it = m_options.begin();
			it != m_options.end(); it++) {
				QString text = it.key();
				core::OptionsBase* widget = it.value();
			
				// add widget to stacked widget
				stackedWidget->addWidget(widget);
				optModules->addItem(text);

		}
		optModules->setCurrentRow(0);
	}
	
	void DlgOptions::entryChanged(QString text)
	{
		if (m_options.find(text) == m_options.end()) {
			qWarning() << "did not find entry " << text;
			return;
		}

		core::OptionsBase* widget = m_options[text];
		optName->setText(text);
		stackedWidget->setCurrentWidget(widget);
	}
	
	void DlgOptions::accept()
	{
		apply();
		QDialog::accept();
	}
	
	void DlgOptions::apply()
	{
		for (QMap<QString, core::OptionsBase*>::const_iterator it = m_options.begin();
			it != m_options.end(); it++) {
			core::OptionsBase* opt = it.value();
			opt->apply();
		}
	}

	void DlgOptions::reject()
	{
		for (QMap<QString, core::OptionsBase*>::const_iterator it = m_options.begin();
			it != m_options.end(); it++) {
			core::OptionsBase* opt = it.value();
			opt->cancel();
		}
		QDialog::reject();
	}
}

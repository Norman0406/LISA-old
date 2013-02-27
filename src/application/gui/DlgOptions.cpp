#include "DlgOptions.h"
#include <core/main/OptionsBase.h>
#include <core/main/Module.h>
#include "MainWindow.h"

namespace lisa
{
	DlgOptions::DlgOptions(const QVector<core::Module*>& modules)
		: QDialog(0), m_currentWidget(0)
	{
		setupUi(this);
		initOptionsWdgs(modules);
	}

	DlgOptions::~DlgOptions()
	{
	}
	
	void DlgOptions::initOptionsWdgs(const QVector<core::Module*>& modules)
	{
		// init options widgets
		for (int i = 0; i < (int)modules.size(); i++) {
			core::Module* mod = modules[i];
			core::OptionsBase* optWdg = mod->getOptionsWdg(this);

			// set default entry if no options dialog is present
			if (!optWdg)
				optWdg = new core::WdgOptionsDefault(this);
			
			// add widget to stacked widget
			int index = stackedWidget->addWidget(optWdg);
			if (index != i)
				qWarning() << "index does not match";

			m_widgets.push_back(QPair<const core::Module*, core::OptionsBase*>(mod, optWdg));
			optModules->addItem(mod->getDisplayName());
		}
		
		optModules->setCurrentRow(0);
	}

	void DlgOptions::moduleChanged(int index)
	{
		optName->setText(m_widgets[index].first->getDisplayName());
		stackedWidget->setCurrentIndex(index);
	}
	
	void DlgOptions::accept()
	{
		apply();
		QDialog::accept();
	}
	
	void DlgOptions::apply()
	{
		for (int i = 0; i < m_widgets.size(); i++) {
			core::OptionsBase* opt = m_widgets[i].second;
			opt->apply();
		}
	}

	void DlgOptions::reject()
	{
		for (int i = 0; i < m_widgets.size(); i++) {
			core::OptionsBase* opt = m_widgets[i].second;
			opt->cancel();
		}
		QDialog::reject();
	}
}

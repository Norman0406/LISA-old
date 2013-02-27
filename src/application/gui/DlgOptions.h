#ifndef LISA_DLGOPTIONS_H
#define LISA_DLGOPTIONS_H

#include "ui_DlgOptions.h"

namespace core
{
	class Module;
	class ModuleBase;
	class OptionsBase;
}

namespace lisa
{

	// options dialog
	class DlgOptions
		: public QDialog, public Ui::DlgOptions
	{
		Q_OBJECT

	public:
		DlgOptions(const QVector<core::Module*>&);
		~DlgOptions();

	public slots:
		void moduleChanged(int);
		void accept();
		void apply();
		void reject();

	private:
		void initOptionsWdgs(const QVector<core::Module*>&);

		QVector<QPair<const core::Module*, core::OptionsBase*>> m_widgets;
		QWidget* m_currentWidget;
	};
}

#endif // LISA_DLGOPTIONS_H

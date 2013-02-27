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
		DlgOptions();
		~DlgOptions();

		void init();

	public slots:
		void entryChanged(QString);
		void accept();
		void apply();
		void reject();

	signals:
		void createOptionWidgets(QMap<QString, core::OptionsBase*>&, QWidget*);

	private:
		QMap<QString, core::OptionsBase*> m_options;
	};
}

#endif // LISA_DLGOPTIONS_H
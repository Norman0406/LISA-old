#include "WdgOptions.h"
#include <QtWidgets/QStyleFactory>
#include <QtWidgets/QListWidget>
#include <core/main/PropertyList.h>

namespace lisa
{
	WdgOptions::WdgOptions(core::PropertyList* properties, const LISAModule* module, QWidget* parent)
		: OptionsBase(properties, module, parent)
	{
		setupUi(this);
		
		m_propStyle = m_properties->getProperty<QString>("Style");

		initStyle();
	}

	WdgOptions::~WdgOptions(void)
	{
	}
	
	void WdgOptions::apply()
	{
		// set changes
		m_propStyle->setValue(lstStyles->currentItem()->text());
		
		// apply
		QApplication::setStyle(QStyleFactory::create(m_propStyle->getValue()));
	}

	void WdgOptions::cancel()
	{
	}

	void WdgOptions::init()
	{
		// retrieve detected modules
		QVector<QString> detectedModules;
		emit fillDetectedModules(detectedModules);
		for (int i = 0; i < detectedModules.size(); i++) {
			QListWidgetItem* item = new QListWidgetItem(lstModules);
			item->setText(detectedModules[i]);
			
			// set checked state only if module is currently loaded
			bool loaded = false;
			emit moduleLoaded(detectedModules[i], loaded);

			if (loaded) {
				item->setTextColor(Qt::black);
				item->setCheckState(Qt::Checked);
			}
			else {
				item->setTextColor(Qt::darkGray);
				item->setCheckState(Qt::Unchecked);
			}

			lstModules->addItem(item);
		}
	}

	void WdgOptions::initStyle()
	{
		QString curName = m_propStyle ? m_propStyle->getValue() : "";
		bool selected = false;

		// enumerate styles
		QStringList styles = QStyleFactory::keys();
		for (int i = 0; i < styles.size(); i++) {
			QString style = styles[i];

			QListWidgetItem* item = new QListWidgetItem(style);
			lstStyles->addItem(item);

			// select current style
			if (curName.toLower() == style.toLower()) {
				lstStyles->setCurrentItem(item);
				selected = true;
			}
		}
				
		if (!selected)
			m_propStyle->setToDefault();
	}
		
	void WdgOptions::deactivate(QListWidgetItem* item)
	{		
		if (item && this->isVisible()) {
			if (item->checkState() == Qt::Checked) {
				item->setTextColor(Qt::black);
				emit enableModule(item->text(), true);
			}
			else {
				item->setTextColor(Qt::darkGray);
				emit enableModule(item->text(), false);
			}
		}
	}
}

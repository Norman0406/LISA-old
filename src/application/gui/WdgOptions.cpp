#include "WdgOptions.h"
#include <QtWidgets/QStyleFactory>
#include <QtWidgets/QListWidget>
#include <core/main/PropertyList.h>

namespace lisa
{
	WdgOptions::WdgOptions(core::PropertyList* properties, QWidget* parent)
		: OptionsBase(properties, parent)
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
}

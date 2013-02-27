#ifndef LISA_WDGLOGGING_H
#define LISA_WDGLOGGING_H

#include "ui_WdgLogging.h"
#include <core/common/Logging.h>

namespace lisa
{
	class WdgLogging
		: public QWidget, public Ui::WdgLogging
	{
		Q_OBJECT

	public:
		WdgLogging(QWidget* parent);
		~WdgLogging(void);

		void addLogEntry(const core::LoggingEntry&);
	};
}

#endif // LISA_WDGLOGGING_H
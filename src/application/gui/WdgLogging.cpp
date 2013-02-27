#include "WdgLogging.h"

namespace lisa
{
	WdgLogging::WdgLogging(QWidget* parent)
		: QWidget(parent)
	{
		setupUi(this);
	}

	WdgLogging::~WdgLogging(void)
	{
	}
	
	void WdgLogging::addLogEntry(const core::LoggingEntry& entry)
	{
		logViewer->setTextColor(entry.m_textCol);
		logViewer->append(entry.m_line);
		//logViewer->moveCursor(QTextCursor::StartOfLine);
	}
}

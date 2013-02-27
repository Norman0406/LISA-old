#include "WdgLogEntry.h"

namespace logbook
{
	WdgLogEntry::WdgLogEntry(QWidget* parent)
		: QWidget(parent)
	{
		setupUi(this);

		reset();
	}

	WdgLogEntry::~WdgLogEntry(void)
	{
	}
	
	void WdgLogEntry::add()
	{
	}

	void WdgLogEntry::cancel()
	{
	}

	void WdgLogEntry::reset()
	{
		logDate->setDate(QDate::currentDate());
		setStartTime();
		logCall->setFocus();	// no effect?
	}
	
	void WdgLogEntry::setStartTime()
	{
		logStart->setTime(QTime::currentTime());
		setEndTime();
	}

	void WdgLogEntry::setEndTime()
	{
		logEnd->setTime(QTime::currentTime());
	}

	void WdgLogEntry::setFreq()
	{
	}

	void WdgLogEntry::setMode()
	{
	}

	void WdgLogEntry::setCallsign(QString callsign)
	{
		// convert text to upper case
		callsign = callsign.toUpper();

		// change tab text
		QString text = "[" + logStart->time().toString(Qt::TextDate) + "] " + callsign;
		emit tabNameChanged(text, this);
		
		// set text
		logCall->setText(callsign);
	}
}

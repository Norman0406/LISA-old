#ifndef DIGITAL_WDGDIGITAL_H
#define DIGITAL_WDGDIGITAL_H

#include "../audio/AudioDeviceIn.h"
#include "../audio/AudioSpectrum.h"
#include "ui_WdgDigital.h"
#include <QtCore/QTimer>

namespace digital
{
	class WdgDigital
		: public QMainWindow, public Ui::WdgDigital
	{
		Q_OBJECT

	public:
		WdgDigital(QWidget*);
		~WdgDigital(void);
		
	public slots:
		void computeSpectrum();

	private:

		AudioDeviceIn*		m_device;
		AudioSpectrum*		m_spectrum;
		QTimer*				m_timer;
	};
}

#endif // DIGITAL_WDGDIGITAL_H

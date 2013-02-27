#include "WdgDigital.h"

#include <QtCore/QTime>

namespace digital
{
	WdgDigital::WdgDigital(QWidget* parent)
		: QMainWindow(parent), m_device(0), m_spectrum(0)
	{
		setupUi(this);
		
		// create spectrum analyzer
		m_spectrum = new AudioSpectrum(4096, WT_BLACKMANHARRIS, this);

		// create waterfall widget
		waterfall->init(m_spectrum->getSpectrumSize());

		// connect spectrum to widget
		connect(m_spectrum, &AudioSpectrum::passbandChanged, waterfall, &WdgWaterfall::setPassband);
		connect(m_spectrum, &AudioSpectrum::dataReady, waterfall, &WdgWaterfall::addSpectrum);
		m_spectrum->init();
		m_spectrum->setPassband(100, 3200);

		// init audio device
		m_device = new AudioDeviceIn(this);
		m_device->init();
		m_device->start();

		// init timer to update the widget
		m_timer = new QTimer(this);
		m_timer->setTimerType(Qt::PreciseTimer);
		const int updateInterval = (1 / 15.0f) * 1000;	// fps
		m_timer->setInterval(updateInterval);
		connect(m_timer, &QTimer::timeout, this, &WdgDigital::computeSpectrum);
		m_timer->start();
	}

	WdgDigital::~WdgDigital(void)
	{
	}
	
	void WdgDigital::computeSpectrum()
	{
		const QByteArray& buffer = m_device->getBuffer(m_spectrum->getFFTSize());
		m_spectrum->compute(m_device->getFormat(), buffer);
	}
}

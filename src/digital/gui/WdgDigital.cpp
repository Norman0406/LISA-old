/***********************************************************************
*
* LISA: Lightweight Integrated System for Amateur Radio
* Copyright (C) 2013 Norman Link <norman.link@gmx.net>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
***********************************************************************/

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

        m_waterfall = new WdgWaterfall(this);
        groupBox_2->layout()->addWidget(m_waterfall);
        m_waterfall->init(m_spectrum->getSpectrumSize());

        // connect spectrum to widget
        connect(m_spectrum, &AudioSpectrum::passbandChanged, m_waterfall, &WdgWaterfall::setPassband);
        connect(m_spectrum, &AudioSpectrum::dataReady, m_waterfall, &WdgWaterfall::addSpectrum);
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

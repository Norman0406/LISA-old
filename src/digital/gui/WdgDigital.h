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

#ifndef DIGITAL_WDGDIGITAL_H
#define DIGITAL_WDGDIGITAL_H

#include "../audio/AudioDeviceIn.h"
#include "../audio/AudioSpectrum.h"
#include "ui_WdgDigital.h"
#include "WdgWaterfall.h"
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
        WdgWaterfall*       m_waterfall;
    };
}

#endif // DIGITAL_WDGDIGITAL_H

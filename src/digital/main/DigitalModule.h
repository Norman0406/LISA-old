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

#ifndef DIGITAL_DIGITALMODULE_H
#define DIGITAL_DIGITALMODULE_H

#include <core/main/Module.h>
#include "../gui/WdgToolbar.h"
#include "../gui/WdgSidebar.h"
#include "../gui/WdgOptions.h"
#include "../gui/WdgWaterfall.h"
#include "../audio/AudioDeviceIn.h"
#include "../audio/AudioSpectrum.h"
#include "ui_WdgDigital.h"
#include <QtCore/QTimer>
#include <QtCore/QThread>
#include <QtCore/QMutex>
#include <QtCore/QDebug>

namespace digital
{
    class DigitalModule
        : public core::Module, public Ui::WdgDigital
    {
        Q_OBJECT
        Q_PLUGIN_METADATA(IID ModulePlugin_iid)
        Q_INTERFACES(core::ModulePlugin)

    public:
        DigitalModule();
        ~DigitalModule(void);

        QString	getModuleName() const;
        QString getDisplayName() const;
        bool isInit() const;

    public slots:
        void getModuleWidgets(core::Module::WidgetType, QWidget*, QVector<QPair<QString, QWidget*> >&);
        
    protected:
        bool iInit(QWidget*);

    private slots:
        void clearOptions();
        void computeSpectrum();

    private:
        WdgToolbar* m_toolbar;
        WdgSidebar* m_sidebar;
        WdgOptions* m_options;
        
        AudioDeviceIn*		m_device;
        AudioSpectrum*		m_spectrum;
        QTimer*				m_timer;
        WdgWaterfall*       m_waterfall;
    };
}

#endif // DIGITAL_DIGITALMODULE_H

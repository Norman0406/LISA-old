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

#ifndef LISA_WDGOPTIONS_H
#define LISA_WDGOPTIONS_H

#include <core/main/OptionsBase.h>
#include <core/main/Property.h>
#include "ui_WdgOptions.h"

namespace lisa
{
    class WdgOptions
        : public core::OptionsBase, public Ui::WdgOptions
    {
        Q_OBJECT

    public:
        WdgOptions(core::PropertyList*, QWidget* parent);
        ~WdgOptions(void);

        void init(const QVector<QPair<QString, bool> >&);

    public slots:
        void apply();
        void cancel();
        void deactivate(QListWidgetItem*);

    signals:
        void enableModule(const QString&, bool);
                
    private:
        void initStyle();

    private:
        core::Property<QString>* m_propStyle;
    };
}

#endif // LISA_WDGOPTIONS_H

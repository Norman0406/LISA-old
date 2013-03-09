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

#ifndef LOGBOOK_WDGSIDEBAR_H
#define LOGBOOK_WDGSIDEBAR_H

#include "ui_WdgSidebar.h"

namespace logbook
{
    class WdgSidebar
        : public QWidget, public Ui::WdgSidebar
    {
        Q_OBJECT

    public:
        WdgSidebar(QWidget* parent);
        ~WdgSidebar(void);
    };
}

#endif // LOGBOOK_WDGSIDEBAR_H

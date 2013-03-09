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
   
#ifndef LOGBOOK_WDGLOGENTRY_H
#define LOGBOOK_WDGLOGENTRY_H

#include "ui_WdgLogEntry.h"

namespace logbook
{
    class WdgLogEntry
        : public QWidget, public Ui::WdgLogEntry
    {
        Q_OBJECT

    public:
        WdgLogEntry(QWidget* parent);
        ~WdgLogEntry(void);

    public slots:
        void add();
        void cancel();
        void reset();
        void setStartTime();
        void setEndTime();
        void setFreq();
        void setMode();
        void setCallsign(QString);

    signals:
        void tabNameChanged(QString, const WdgLogEntry*);
    };
}

#endif // LOGBOOK_WDGLOGENTRY_H
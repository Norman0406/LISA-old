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

#ifndef LOGBOOK_QSOENTRY_H
#define LOGBOOK_QSOENTRY_H

#include "QSOFieldBase.h"
#include <QtCore/QVector>

namespace logbook
{
    class QSOEntry
    {
    public:
        QSOEntry();
        ~QSOEntry();

        void clear();
        void addField(const QSOFieldBase&);

    private:
        void initStandardFields();
        void clear(QVector<QSOFieldBase*>&);
        void addField(const QSOFieldBase&, QVector<QSOFieldBase*>&);

        QVector<QSOFieldBase*> m_standardFields;
        QVector<QSOFieldBase*> m_additionalFields;

        //QSOLayout	m_layout;
    };
}

#endif // LOGBOOK_QSOENTRY_H
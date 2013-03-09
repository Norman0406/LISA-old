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

#include "QSOEntry.h"
#include "QSOField.h"

namespace logbook
{
    QSOEntry::QSOEntry()
    {
        initStandardFields();
    }

    QSOEntry::~QSOEntry()
    {
        clear();
    }

    void QSOEntry::clear()
    {
        clear(m_standardFields);
        clear(m_additionalFields);
    }
    
    void QSOEntry::clear(QVector<QSOFieldBase*>& fields)
    {
        for (int i = 0; i < fields.size(); i++)
            delete fields[i];
        fields.clear();
    }

    void QSOEntry::addField(const QSOFieldBase& field)
    {
        addField(field, m_additionalFields);
    }

    void QSOEntry::addField(const QSOFieldBase& field, QVector<QSOFieldBase*>& fields)
    {
        Q_UNUSED(field);
        Q_UNUSED(fields);
    }

    void QSOEntry::initStandardFields()
    {
        addField(QSOField<QDate>("Date"));
        addField(QSOField<QTime>("Start"));
        addField(QSOField<QTime>("End"));
        addField(QSOField<QString>("Callsign"));
        addField(QSOField<int>("RSTsent"));
        addField(QSOField<int>("RSTrcvd"));
        addField(QSOField<float>("Freq"));
        addField(QSOField<QString>("Mode"));
        addField(QSOField<QString>("Country"));
        addField(QSOField<QString>("Locator"));
        addField(QSOField<QString>("Comment"));	
    }
}

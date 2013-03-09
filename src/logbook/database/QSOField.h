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

#ifndef LOGBOOK_QSOFIELD_H
#define LOGBOOK_QSOFIELD_H

#include "QSOFieldBase.h"

#include <QtCore/QDate>
#include <QtCore/QTime>

namespace logbook
{
    template <typename T>
    class QSOField
        : public QSOFieldBase
    {
    public:
        QSOField(QString);
        ~QSOField();
        
        QString getTypeStr() const;
        QString getValueStr() const;
    };

    // template implementation
    template <typename T>
    QSOField<T>::QSOField(QString name)
        : QSOFieldBase(name)
    {
    }
    
    template <typename T>
    QSOField<T>::~QSOField()
    {
    }
    
    template <typename T>
    QString QSOField<T>::getTypeStr() const
    {
        return "";
    }
    
    template <typename T>
    QString QSOField<T>::getValueStr() const
    {
        return "";
    }
}

#endif // LOGBOOK_QSOFIELD_H
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

#ifndef DIGITAL_COLORMAP_H
#define DIGITAL_COLORMAP_H

#include <QtCore/QObject>
#include <QtCore/QMap>
#include <QtGui/QColor>

namespace digital
{
    class ColormapVisitor;

    class Colormap
        : public QObject
    {
        Q_OBJECT

    public:
        Colormap(int, QObject*);
        ~Colormap();

        void accept(ColormapVisitor&);
        void addColor(int, const QColor&);
        int getRange() const;
        QColor getColorValue(int);

        
    private:
        void clear();
        void buildColorTable();

        QMap<int, QColor> m_colors;
        QColor* m_colorTable;
        int m_range;
    };
}

#endif // DIGITAL_COLORMAP_H

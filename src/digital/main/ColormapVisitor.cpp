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

#include "ColormapVisitor.h"
#include "Colormap.h"

namespace digital
{	
    /************************************************************************
       ColormapBlue
    ************************************************************************/
    void ColormapBlue::visit(Colormap& map)
    {
        int range = map.getRange();
        map.addColor(0, QColor(0, 0, 30));
        map.addColor((int)(range / 3.0), QColor(0, 0, 83));
        map.addColor(range - 1, QColor(255, 255, 255));
    }

    /************************************************************************
       ColormapFldigi
    ************************************************************************/
    void ColormapFldigi::visit(Colormap& map)
    {
        int range = map.getRange();
        map.addColor(0, QColor(0, 0, 0));
        map.addColor((int)((43 / 255.0) * range), QColor(0, 0, 255));
        map.addColor((int)((87 / 255.0) * range), QColor(0, 255, 255));
        map.addColor((int)((120 / 255.0) * range), QColor(0, 255, 0));
        map.addColor((int)((154 / 255.0) * range), QColor(255, 255, 0));
        map.addColor((int)((217 / 255.0) * range), QColor(255, 0, 0));
        map.addColor(range - 1, QColor(255, 0, 128));
    }
}
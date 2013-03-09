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

#ifndef DIGITAL_COLORMAPVISITOR_H
#define DIGITAL_COLORMAPVISITOR_H

namespace digital
{
    class Colormap;

    /************************************************************************
       ColormapVisitor: simple visitor class for special color maps
    ************************************************************************/
    class ColormapVisitor
    {
    public:
        virtual void visit(Colormap&) = 0;
    };
    
    /************************************************************************
       ColormapBlue
    ************************************************************************/
    class ColormapBlue
        : public ColormapVisitor
    {
    public:
        void visit(Colormap&);
    };
    
    /************************************************************************
       ColormapFldigi: sorry, this is not Fldigi's default, it's CuteSDR's
    ************************************************************************/
    class ColormapFldigi
        : public ColormapVisitor
    {
    public:
        void visit(Colormap&);
    };
}

#endif // DIGITAL_COLORMAPVISITOR_H
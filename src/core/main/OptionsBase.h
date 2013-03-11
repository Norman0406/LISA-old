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

#ifndef CORE_OPTIONSBASE_H
#define CORE_OPTIONSBASE_H

#include <QtWidgets/QtWidgets>

namespace core
{
    class PropertyList;
    class Module;

    // base class for a widget inside the options dialog
    class OptionsBase
        : public QWidget
    {
        Q_OBJECT

    public:
        virtual ~OptionsBase();
        
        virtual void apply() = 0;
        virtual void cancel() = 0;
        
    protected:
        OptionsBase(PropertyList*, QWidget* parent);

        PropertyList*	m_properties;
    };

    // a default options widgets
    class WdgOptionsDefault
        : public OptionsBase
    {
    public:
        WdgOptionsDefault(QWidget*);
        ~WdgOptionsDefault();
        
        void apply();
        void cancel();
    };
}

#endif // CORE_OPTIONSBASE_H

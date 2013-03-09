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

#include "OptionsBase.h"
#include "PropertyList.h"
#include "Module.h"

namespace core
{
    OptionsBase::OptionsBase(PropertyList* properties, const Module* module, QWidget* parent)
        : QWidget(parent), m_properties(properties), m_module(module)
    {
    }

    OptionsBase::~OptionsBase()
    {
    }
    
    WdgOptionsDefault::WdgOptionsDefault(const Module* module, QWidget* parent)
        : OptionsBase(0, module, parent)
    {
        QLabel* label = new QLabel("This module does not have any options.", this);
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        QVBoxLayout* layout = new QVBoxLayout(this);
        layout->addWidget(label);
        setLayout(layout);
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    }

    WdgOptionsDefault::~WdgOptionsDefault()
    {
    }

    void WdgOptionsDefault::apply()
    {
    }

    void WdgOptionsDefault::cancel()
    {
    }
}

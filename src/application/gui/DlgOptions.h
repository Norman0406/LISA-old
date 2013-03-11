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

#ifndef LISA_DLGOPTIONS_H
#define LISA_DLGOPTIONS_H

#include "ui_DlgOptions.h"

namespace core
{
    class Module;
    class OptionsBase;
}

namespace lisa
{
    class MainWindow;

    // options dialog
    class DlgOptions
        : public QDialog, public Ui::DlgOptions
    {
        Q_OBJECT

    public:
        DlgOptions();
        ~DlgOptions();

        void init(QVector<QPair<QString, core::OptionsBase*> >&);

    public slots:
        void entryChanged(QString);
        void accept();
        void apply();
        void reject();
        void addWidget(core::Module*);
        void removeWidget();
        
    private:
        void addWidgets(QVector<QPair<QString, core::OptionsBase*> >&);

        QVector<QPair<QString, core::OptionsBase*> > m_options;
    };
}

#endif // LISA_DLGOPTIONS_H

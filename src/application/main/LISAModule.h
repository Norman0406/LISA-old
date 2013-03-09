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

#ifndef LISA_LISAMODULE_H
#define LISA_LISAMODULE_H

#include <core/common/Logging.h>
#include <core/main/Module.h>
#include "../gui/MainWindow.h"

namespace lisa
{
    class LISAModule
        : public core::Module
    {
        Q_OBJECT

    public:
        LISAModule();
        ~LISAModule(void);
        
        QString	getModuleName() const;
        QString getDisplayName() const;
        bool isInit() const;
        
        bool createWindow();
        
        MainWindow* getWindow();
        core::OptionsBase* getOptionsWdg(QWidget*);
        
        QByteArray saveGeometry();
        bool restoreGeometry(const QByteArray&);
        QByteArray saveState();
        bool restoreState(const QByteArray&);

    public slots:
        void createOptionWidgets(QVector<QPair<QString, core::OptionsBase*> >&, QWidget*);

    signals:
        void fillDetectedModules(QVector<QString>&);
        void moduleLoaded(const QString&, bool&);
        void enableModule(const QString&, bool);

    protected:
        bool iInit(QWidget*);

    private:
        MainWindow* m_mainWindow;
    };
}

#endif // LISA_LISAMODULE_H

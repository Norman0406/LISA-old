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

#ifndef CORE_MODULE_H
#define CORE_MODULE_H

#include <QtWidgets/QMainWindow>
#include "../common/Exception.h"
#include "../common/Logging.h"
#include "OptionsBase.h"
#include "ModulePlugin.h"
#include "PropertyContainer.h"

namespace core
{
    class Module
        : public ModulePlugin, public PropertyContainer
    {
        Q_OBJECT

    public:
        enum WidgetType
        {
            WT_MAIN,
            WT_TOOLBAR,
            WT_SIDEBAR,
            WT_OPTIONS,
        };
        
        virtual ~Module(void);
                
        // initializing
        bool init(QWidget*);
        virtual bool isInit() const;
        
        virtual QByteArray saveGeometry();
        virtual bool restoreGeometry(const QByteArray&);
        virtual QByteArray saveState();
        virtual bool restoreState(const QByteArray&);

    public slots:
        virtual void getModuleWidgets(core::Module::WidgetType, QWidget*, QVector<QPair<QString, QWidget*> >&);
        virtual void msgReceive(QString, const QVariant&);

    signals:
        void msgSend(QString, const QVariant&);
        void msgRegister(QString);

    protected:
        Module();

        virtual void iPostInitAll();
                
    private:
        bool			m_isInit;
        QWidget*		m_parent;
    };
}

#endif // CORE_MODULE_H

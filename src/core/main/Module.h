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
#include "PropertyList.h"
#include "OptionsBase.h"
#include "ModuleBase.h"

namespace core
{
    class Module
        : public ModuleBase
    {
        Q_OBJECT

    public:
        enum WidgetType
        {
            WT_MAIN,
            WT_TOOLBAR,
            WT_SIDEBAR,
        };
        
        struct ModuleWidget
        {
            WidgetType type;
            QString text;
            QWidget* widget;
        };

        virtual ~Module(void);
                
        // initializing
        bool init(QWidget*);
        virtual bool postInitAll();
        virtual bool isInit() const;
        
        const QVector<ModuleWidget*>& getModuleWidgets();
        QVector<ModuleWidget*> getModuleWidgets(WidgetType);
        
        // property management
        template <typename T>
        bool addProperty(const QString& name, const T& defaultVal);

        template <typename T>
        Property<T>* getProperty(const QString& name);
        
        bool loadProperties();
        bool saveProperties();
        
        virtual QByteArray saveGeometry() = 0;
        virtual bool restoreGeometry(const QByteArray&) = 0;
        virtual QByteArray saveState() = 0;
        virtual bool restoreState(const QByteArray&) = 0;

    public slots:
        virtual void createOptionWidgets(QVector<QPair<QString, core::OptionsBase*> >&, QWidget*);
        virtual void msgReceive(QString, const QVariant&);

    signals:
        void moduleWidgetAdded(WidgetType, const QString&, QWidget*);
        void msgSend(QString, const QVariant&);
        void msgRegister(QString);

    protected:
        Module();

        void addModuleWidget(WidgetType, const QString&, QWidget*);
        virtual void iPostInitAll();
        
        PropertyList m_properties;
        
    private:
        bool			m_isInit;
        QWidget*		m_parent;
        QVector<ModuleWidget*> m_moduleWidgets;
    };
    
    template <typename T>
    bool Module::addProperty(const QString& name, const T& defaultVal)
    {
        return m_properties.addProperty(Property<T>(name, defaultVal));
    }
    
    template <typename T>
    Property<T>* Module::getProperty(const QString& name)
    {
        return m_properties.getProperty<T>(name);
    }
}

#endif // CORE_MODULE_H

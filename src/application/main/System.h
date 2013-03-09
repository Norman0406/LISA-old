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

#ifndef LISA_SYSTEM_H
#define LISA_SYSTEM_H

#include <QtWidgets/QApplication>
#include <QtCore/QVector>
#include <core/common/Logging.h>

namespace core
{
    class Module;
}

namespace lisa
{
    class LISAModule;

    // singleton
    class System
        : public QObject
    {
        Q_OBJECT

    public:
        ~System(void);

        static System* init(int argc, char *argv[]);

        int run();
        
    private slots:
        void msgRegister(QString);
        void msgSend(QString, const QVariant&);
        void enableModule(const QString&, bool);
        void fillDetectedModule(QVector<QString>&);
        void moduleLoaded(const QString&, bool&);
        
    private:
        System(int argc, char *argv[]);

        bool init();

        bool removeModule(core::Module*);
        bool initModule(core::Module*);
        bool initModules();
        void applyProperties();
        void detectModules();
        void loadModules();
        core::Module* loadModule(const QString&);
        bool isModuleLoaded(const QString&);
        
        void loadState();
        void saveState();

        static System*		m_instance;
        QApplication		m_application;
        LISAModule*			m_mainModule;
        core::Logging*		m_logging;

        QMap<QString, QString> m_detectedModules;

        QVector<core::Module*>	m_modules;
        QMap<QString, QPair<QByteArray, QByteArray> > m_stateInfo;
        QMap<QString, QVector<core::Module*> > m_registeredMessages;
    };
}

#endif // LISA_SYSTEM_H

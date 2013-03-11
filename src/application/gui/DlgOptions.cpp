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

#include "DlgOptions.h"
#include <core/main/OptionsBase.h>
#include <core/main/Module.h>
#include "MainWindow.h"

namespace lisa
{
    DlgOptions::DlgOptions()
        : QDialog(0), m_options(0)
    {
        setupUi(this);
    }

    DlgOptions::~DlgOptions()
    {
    }

    void DlgOptions::init(QVector<QPair<QString, core::OptionsBase*> >& widgets)
    {
        optModules->clear();
        addWidgets(widgets);
        optModules->setCurrentRow(0);
    }

    void DlgOptions::addWidgets(QVector<QPair<QString, core::OptionsBase*> >& widgets)
    {
        for (int i = 0; i < widgets.size(); i++) {
            QString text = widgets[i].first;
            core::OptionsBase* widget = widgets[i].second;
            
            // add widget to stacked widget
            stackedWidget->addWidget(widget);

            QListWidgetItem* item = new QListWidgetItem(0);
            item->setText(text);
            optModules->addItem(item);

            m_options.push_back(QPair<QString, core::OptionsBase*>(text, widget));
        }
    }
    
    void DlgOptions::entryChanged(QString text)
    {
        core::OptionsBase* widget = 0;
        for (int i = 0; i < m_options.size(); i++) {
            QString val = m_options[i].first;
            if (val == text) {
                widget = m_options[i].second;
                break;
            }
        }

        if (!widget) {
            qWarning() << "did not find entry " << text;
            return;
        }
        
        optName->setText(text);
        stackedWidget->setCurrentWidget(widget);
    }
    
    void DlgOptions::addWidget(core::Module* module)
    {
        QVector<QPair<QString, QWidget*> > modOpt;
        QVector<QPair<QString, core::OptionsBase*> > optWidgets;
        module->getModuleWidgets(core::Module::WT_OPTIONS, this, modOpt);

        for (int i = 0; i < modOpt.size(); i++) {
            core::OptionsBase* options = (core::OptionsBase*)modOpt[i].second;
            connect(options, &core::OptionsBase::destroyed, this, &DlgOptions::removeWidget);
            optWidgets.push_back(QPair<QString, core::OptionsBase*>(modOpt[i].first, options));
        }

        addWidgets(optWidgets);
    }

    void DlgOptions::removeWidget()
    {
        QObject* wdg = sender();

        if (wdg && isVisible()) {
            core::OptionsBase* widget = 0;
            for (QVector<QPair<QString, core::OptionsBase*> >::iterator it = m_options.begin();
                it != m_options.end(); it++) {
                    if (it->second == wdg) {
                        widget = it->second;

                        // remove from internal list
                        m_options.erase(it);

                        break;
                    }
            }
            
            if (!widget) {
                qWarning() << "did not find entry";
                return;
            }
                        
            // remove item from list
            QListWidgetItem* item = optModules->item(stackedWidget->indexOf(widget));
            delete item;
        }
    }
    
    void DlgOptions::accept()
    {
        apply();
        QDialog::accept();
    }
    
    void DlgOptions::apply()
    {
        for (int i = 0; i < m_options.size(); i++)
            m_options[i].second->apply();
    }

    void DlgOptions::reject()
    {
        for (int i = 0; i < m_options.size(); i++)
            m_options[i].second->cancel();
        QDialog::reject();
    }
}

#include "DlgOptions.h"
#include <core/main/OptionsBase.h>
#include <core/main/Module.h>
#include "MainWindow.h"

namespace lisa
{
    DlgOptions::DlgOptions()
        : QDialog(0)
    {
        setupUi(this);
    }

    DlgOptions::~DlgOptions()
    {
    }

    void DlgOptions::init()
    {
        m_options.clear();
        optModules->clear();
        createOptionWidgets(m_options, this);

        for (int i = 0; i < m_options.size(); i++) {
            QString text = m_options[i].first;
            core::OptionsBase* widget = m_options[i].second;

            connect(widget, &core::OptionsBase::destroyed, this, &DlgOptions::removeWidget);
            
            // add widget to stacked widget
            stackedWidget->addWidget(widget);

            QListWidgetItem* item = new QListWidgetItem(optModules);
            item->setText(text);

            optModules->addItem(item);
        }
        optModules->setCurrentRow(0);
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
    
    void DlgOptions::addWidget()
    {
        QObject* wdg = sender();

        if (wdg) {
            // UNDONE
        }
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

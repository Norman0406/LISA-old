#ifndef LISA_WDGOPTIONS_H
#define LISA_WDGOPTIONS_H

#include <core/main/OptionsBase.h>
#include <core/main/Property.h>
#include "../main/LISAModule.h"
#include "ui_WdgOptions.h"

namespace lisa
{
    class WdgOptions
        : public core::OptionsBase, public Ui::WdgOptions
    {
        Q_OBJECT

    public:
        WdgOptions(core::PropertyList*, const LISAModule*, QWidget* parent);
        ~WdgOptions(void);

        void init();

    public slots:
        void apply();
        void cancel();
        void deactivate(QListWidgetItem*);

    signals:
        void fillDetectedModules(QVector<QString>&);
        void moduleLoaded(const QString&, bool&);
        void enableModule(const QString&, bool);
                
    private:
        void initStyle();

    private:
        core::Property<QString>* m_propStyle;
    };
}

#endif // LISA_WDGOPTIONS_H

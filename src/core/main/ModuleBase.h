#ifndef CORE_MODULEBASE_H
#define CORE_MODULEBASE_H

#include <QtCore/QString>
#include <QtCore/QtPlugin>

namespace core
{
	class ModuleBase
		: public QObject
	{
		Q_OBJECT

	public:
		virtual ~ModuleBase(void) { }
		
		// module identifying functions
		virtual QString	getModuleName() const = 0;
		virtual QString getDisplayName() const = 0;
		
	protected:
		virtual bool iInit(QWidget*) = 0;
	};
}

#define ModuleBase_iid "LISA.core.modulebase"
Q_DECLARE_INTERFACE(core::ModuleBase, ModuleBase_iid)

#endif // CORE_MODULEBASE_H

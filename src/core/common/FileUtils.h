#ifndef CORE_FILEUTILS_H
#define CORE_FILEUTILS_H

#include <QtCore/QString>

namespace core
{
	enum SystemFolder
	{
		SF_APPLICATION,
		SF_CONFIG,
	};

	// pure static
	class FileUtils
	{
	public:
		static QString getFolderStr(SystemFolder);
		static QString openFolder(SystemFolder folder, bool create);
		static QString openFolder(QString folder, bool create);
	};
}

#endif // CORE_FILEUTILS_H
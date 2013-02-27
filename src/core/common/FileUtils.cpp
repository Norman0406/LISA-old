#include "FileUtils.h"
#include <QtGui/QGuiApplication>
#include <QtCore/QDir>

namespace core
{
	QString FileUtils::getFolderStr(SystemFolder folder)
	{
		switch (folder) {
		case SF_APPLICATION:
			return qApp->applicationDirPath();
		case SF_CONFIG:
			return qApp->applicationDirPath() + "/cfg/";
		}

		return "<invalid>";
	}
	
	QString FileUtils::openFolder(SystemFolder folder, bool create)
	{
		return openFolder(getFolderStr(folder), create);
	}

	QString FileUtils::openFolder(QString folder, bool create)
	{
		if (!QDir(folder).exists()) {
			if (create) {
				QDir().mkdir(folder);
				return folder;
			}
			else
				return QString();
		}

		return folder;
	}
}

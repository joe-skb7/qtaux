#include <QtCore/QDir>
#include <QtCore/QFileInfo>
#include "qxsys/qxpathprober.h"

namespace {
    const QString ConfigDir = ".config";
} // anonymous namespace

QString QxPathProber::configDirPath()
{
    QString configPath = QDir::homePath() + QDir::separator() + ConfigDir;
    QFileInfo configPathInfo(configPath);
    if (!configPathInfo.isDir()) {
        QDir configDir;
        if (!configDir.mkpath(configPath))
            return QString();
    }

    return configPath;
}

#include <QtCore/QFileInfo>
#include <QtCore/QDir>
#include <QtCore/QProcessEnvironment>
#include <QtCore/QTextCodec>
#include "qxsys/qxpathprober.h"

namespace {
    const char *AppDataVarName = "APPDATA";
} // anonymous namespace

QString QxPathProber::configDirPath()
{
    // Caching
    static QString cashedAppDataPath;
    if (!cashedAppDataPath.isEmpty())
        return cashedAppDataPath;

    QProcessEnvironment environment = QProcessEnvironment::systemEnvironment();
    QString appDataPath = QTextCodec::codecForName("System")->toUnicode(
                environment.value(AppDataVarName).toLocal8Bit());

    if (appDataPath.isEmpty())
        return appDataPath;

    if (appDataPath.endsWith(QDir::separator()) || appDataPath.endsWith('/')
            || (appDataPath.endsWith('\\')))
        appDataPath.chop(1);

    QFileInfo appDataPathInfo(appDataPath);
    if (!appDataPathInfo.isDir())
        return QString();

    return cashedAppDataPath = appDataPath;
}

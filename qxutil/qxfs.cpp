#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QStringList>
#include "qxutil/qxfs.h"

/*!
    Removes directory \a dirPath recursively (with all content).
*/
bool QxFs::rmrf(const QString &dirPath)
{
    QDir dir(dirPath);

    // Getting directories list
    QStringList dirList = dir.entryList(QDir::Dirs  | QDir::AllDirs | QDir::NoDotAndDotDot);
    // Getting files list
    QStringList fileList = dir.entryList(QDir::Files);

    // Removing files
    foreach (QString entry, fileList) {
        QString entryAbsPath = dir.absolutePath() + "/" + entry;
        // Setting up permissions for removing file
        QFile::setPermissions(entryAbsPath, QFile::WriteOwner | QFile::WriteUser | QFile::WriteGroup
                              | QFile::WriteOther);
        if (!QFile::remove(entryAbsPath))
            return false;
    }

    // Recursive removing directories
    foreach (QString entry, dirList) {
        QString entryAbsPath = dir.absolutePath() + "/" + entry;
        if (!QxFs::rmrf(entryAbsPath))
            return false;
    }

    // Removing processed directory
    if (!QDir().rmdir(dir.absolutePath()))
        return false;

    return true;
}

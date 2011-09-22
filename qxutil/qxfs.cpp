/****************************************************************************
**
** The code is licensed under the 2-clause, simplified BSD license.
**
** Copyright 2011 Sam Protsenko. All rights reserved.
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**
**   1. Redistributions of source code must retain the above copyright
**      notice, this list of conditions and the following disclaimer.
**
**   2. Redistributions in binary form must reproduce the above copyright
**      notice, this list of conditions and the following disclaimer in
**      the documentation and/or other materials provided with the
**      distribution.
**
** THIS SOFTWARE IS PROVIDED BY <COPYRIGHT HOLDER> ''AS IS'' AND ANY
** EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
** IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
** PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> OR
** CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
** EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
** PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
** PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
** LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
** NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
** SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
** The views and conclusions contained in the software and documentation
** are those of the authors and should not be interpreted as representing
** official policies, either expressed or implied, of Sam Protsenko.
**
****************************************************************************/

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

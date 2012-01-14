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
** THIS SOFTWARE IS PROVIDED BY SAM PROTSENKO ''AS IS'' AND ANY
** EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
** IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
** PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL SAM PROTSENKO OR
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

#include <QtCore/QDebug>
#include <QtCore/QSettings>
#include "qxsys/qxstartupprovider.h"

namespace {
    const QString RegistryStartupPath = "HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\"
            "CurrentVersion\\Run";
} // anonymous namespace

QString QxStartupProvider::appStartFilePath(const QString &appName)
{
    QSettings settings(RegistryStartupPath, QSettings::NativeFormat);
    if (!settings.contains(appName))
        return QString();
    QString path = settings.value(appName).toString();

    if (path.contains("\""))
        path.replace("\"", "");

    return path;
}

bool QxStartupProvider::isAppRegistered(const QString &appName)
{
    QSettings settings(RegistryStartupPath, QSettings::NativeFormat);
    return settings.contains(appName);
}

bool QxStartupProvider::registerApp(const QString &appName, const QString &filePath)
{
    QSettings settings(RegistryStartupPath, QSettings::NativeFormat);
    QString nativeFilePath = filePath;
    nativeFilePath.replace("/", "\\");
    settings.setValue(appName, "\"" + nativeFilePath + "\"");
    return settings.status() == QSettings::NoError;
}

bool QxStartupProvider::removeApp(const QString &appName)
{
    QSettings settings(RegistryStartupPath, QSettings::NativeFormat);
    settings.remove(appName);
    return settings.status() == QSettings::NoError;
}

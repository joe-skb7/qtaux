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

#include <windows.h>
#include <QtCore/QString>
#include <QtCore/QSysInfo>
#include "qxsys/qxosprober.h"

QString QxOsProber::osName()
{
    switch (QSysInfo::windowsVersion()) {
    case QSysInfo::WV_32s:       return "Windows 3.1";
    case QSysInfo::WV_95:        return "Windows 95";
    case QSysInfo::WV_98:        return "Windows 98";
    case QSysInfo::WV_Me:        return "Windows Me";
    case QSysInfo::WV_DOS_based: return "MS-DOS-based version of Windows";

    case QSysInfo::WV_NT:        return "Windows NT";
    case QSysInfo::WV_2000:      return "Windows 2000";
    case QSysInfo::WV_XP:        return "Windows XP";
    case QSysInfo::WV_2003:      return "Windows Server 2003";
    case QSysInfo::WV_VISTA:     return "Windows Vista";
    case QSysInfo::WV_WINDOWS7:  return "Windows 7";
    case QSysInfo::WV_NT_based:  return "NT-based version of Windows";

    case QSysInfo::WV_CE:        return "Windows CE";
    case QSysInfo::WV_CENET:     return "Windows CE .NET";
    case QSysInfo::WV_CE_5:      return "Windows CE 5.x";
    case QSysInfo::WV_CE_6:      return "Windows CE 6.x";
    case QSysInfo::WV_CE_based:  return "CE-based version of Windows";

    default:                     return "";
    }
}

int QxOsProber::servicePackNumber()
{
    OSVERSIONINFOA osVersion;
    ZeroMemory(&osVersion, sizeof(OSVERSIONINFOA));
    osVersion.dwOSVersionInfoSize = sizeof(OSVERSIONINFOA);
    GetVersionExA(&osVersion);

    QString sp(osVersion.szCSDVersion);
    sp = sp.trimmed();
    if (sp.contains("Service Pack")) {
        QString numberString = sp.at(sp.size() - 1);
        bool ok;
        int number = numberString.toInt(&ok);
        if (ok)
            return number;
        else
            return 0;
    } else {
        return 0;
    }

    return 0;
}

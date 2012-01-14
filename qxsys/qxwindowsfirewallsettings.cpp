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

#include <QtCore/QSettings>
#include <QtCore/QSysInfo>
#include <QtCore/QTextCodec>
#include <cstring>
#include <windows.h>
#include "qxsys/qxwindowsfirewallsettings.h"
#include "qxsys/qxosprober.h"

namespace {
    const QString Win7Path  = "HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\services\\"
                              "SharedAccess\\Parameters\\FirewallPolicy\\FirewallRules";

    const QString WinXpPath = "SYSTEM\\CurrentControlSet\\services\\"
                              "SharedAccess\\Parameters\\FirewallPolicy\\StandardProfile";
    const QString WinXpPort = "GloballyOpenPorts\\List";
    const QString WinXpApp  = "AuthorizedApplications\\List";
    const QString EnString = ":*:Enabled:";
} // anonymous namespace

/*!
    \class QxWindowsFirewallSettings
    \brief Provides functions that creates Windows firewall rules.
    \todo Add removing and checking existed rules.
*/

QxWindowsFirewallSettings::QxWindowsFirewallSettings()
    : m_errorOccurred(false)
{
}

/*!
    Checks up if OS is supported by this class.
*/
bool QxWindowsFirewallSettings::isOsSupported()
{
    switch (QSysInfo::windowsVersion()) {
    case QSysInfo::WV_XP:
        return QxOsProber::servicePackNumber() >= 2;
    case QSysInfo::WV_VISTA:
    case QSysInfo::WV_WINDOWS7:
        return true;
    default:
        return false;
    }

    return false;
}

/*!
    Creates Windows firewall rule; this function creates exception for application.
    \param ruleName Rule name.
    \param uuid Application identifier; must be a string "{AAAAAAAA-BBBB-CCCC-DDDD-EEEEEEEEEEEE}".
    \param appPath Application executable file path; use separator "\".
    \param description Rule description.
    \param protocol Protocol for which rule creates.
    \note There is unique \a uuid must be used for each rule, i.e. if create 2 rules for application
    (UDP and TCP) - for those rules must be used different \a uuid values.
*/
bool QxWindowsFirewallSettings::createFirewallException(const QString &ruleName, const QUuid &uuid,
        const QString &appPath, const QString &description, Protocol protocol)
{
    QString uuidString = uuid.toString().toUpper();
    QString winAppPath = appPath;
    winAppPath.replace("/", "\\");

    switch (QSysInfo::windowsVersion()) {
    case QSysInfo::WV_XP: {
            QTextCodec *loc = QTextCodec::codecForLocale();
            QTextCodec::setCodecForLocale(QTextCodec::codecForName("System"));

            const QString regAppPath = WinXpPath + "\\" + WinXpApp;
            const QString appKey = winAppPath;
            const QString appValue = appKey + EnString + ruleName;

            // Converting to char*
            const QByteArray regAppPathBa = regAppPath.toLocal8Bit();
            const char *regAppPathCString = regAppPathBa.data();
            const QByteArray appKeyBa = appKey.toLocal8Bit();
            const char *appKeyCString = appKeyBa.data();
            const QByteArray appValueBa = appValue.toLocal8Bit();
            const char *appValueCString = appValueBa.data();

            {
                HKEY key;
                LONG res = RegOpenKeyExA(HKEY_LOCAL_MACHINE, regAppPathCString, 0,
                                         KEY_SET_VALUE, &key);
                if (res != ERROR_SUCCESS) {
                    m_errorOccurred = true;
                    m_errorString = "Unable to open key " + regAppPath;
                    QTextCodec::setCodecForLocale(loc);
                    return false;
                }

                RegSetValueExA(key, appKeyCString, 0, REG_SZ, (BYTE*)appValueCString,
                               strlen(appValueCString) + 1);
                RegCloseKey(key);
            }

            QTextCodec::setCodecForLocale(loc);

            break;
        }
    case QSysInfo::WV_VISTA:
    case QSysInfo::WV_WINDOWS7: {
            QSettings registry(Win7Path, QSettings::NativeFormat);
            registry.setValue(uuidString,
                                "v2.10|Action=Allow|Active=TRUE|Dir=In"
                                "|Protocol=" + QString::number(protocolNumber(protocol))
                              + "|App=" + winAppPath
                              + "|Name=" + ruleName
                              + "|Desc=" + description
                              + "|Edge=TRUE|");
            if (!checkSettingsStatus(registry))
                return false;

            registry.sync();
            if (!checkSettingsStatus(registry))
                return false;

            break;
        }
    default:
        m_errorOccurred = true;
        m_errorString = "Unsupported Windows version: "
                + QString::number(QSysInfo::windowsVersion());
        return false;
    }

    return true;
}

/*!
    \overload

    Creates rule for Windows firewall; this function creates exception for port.
    \param ruleName Rule name.
    \param protocol Protocol for which rule creates.
    \param port Port that opened by rule.

    \warning Only for WindowsXP.
*/
bool QxWindowsFirewallSettings::createFirewallException(const QString &ruleName, Protocol protocol,
                                                      int port)
{
    if (!QSysInfo::windowsVersion() == QSysInfo::WV_XP)
        return false;


    QTextCodec *loc = QTextCodec::codecForLocale();
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("System"));

    const QString regPortPath = WinXpPath + "\\" + WinXpPort;
    const QString portKey = QString::number(port) + ":" + protocolString(protocol);
    const QString portValue = portKey + EnString + ruleName;

    // Converting to char*
    const QByteArray regPortPathBa = regPortPath.toLocal8Bit();
    const char *regPortPathCString = regPortPathBa.data();
    const QByteArray portKeyBa = portKey.toLocal8Bit();
    const char *portKeyCString = portKeyBa.data();
    const QByteArray portValueBa = portValue.toLocal8Bit();
    const char *portValueCString = portValueBa.data();

    {
        HKEY key;
        LONG res = RegOpenKeyExA(HKEY_LOCAL_MACHINE, regPortPathCString, 0,
                                 KEY_SET_VALUE, &key);
        if (res != ERROR_SUCCESS) {
            m_errorOccurred = true;
            m_errorString = "Unable to open key " + regPortPath;
            QTextCodec::setCodecForLocale(loc);
            return false;
        }
        RegSetValueExA(key, portKeyCString, 0, REG_SZ, (BYTE*)portValueCString,
                       strlen(portValueCString) + 1);
        RegCloseKey(key);
    }

    QTextCodec::setCodecForLocale(loc);
    return true;
}

/*!
    Returns \a true if error has been occurred.
*/
bool QxWindowsFirewallSettings::errorOccurred() const
{
    return m_errorOccurred;
}

/*!
    Returns last occurred error string.
*/
QString QxWindowsFirewallSettings::errorString() const
{
    return m_errorString;
}

/* private */

/*!
    Returns protocol number that uses in firewall rule string at registry
    (for Windows Vista/7 firewall).
    \return -1 If error occurred.
*/
int QxWindowsFirewallSettings::protocolNumber(Protocol protocol) const
{
    switch (protocol) {
    case Tcp:
        return 6;
    case Udp:
        return 17;
    }

    m_errorOccurred = true;
    m_errorString = "Unknown protocol type " + QString::number(protocol);
    return -1;
}

/*!
    Returns protocol string (for Windows XP firewall).
*/
QString QxWindowsFirewallSettings::protocolString(Protocol protocol) const
{
    switch (protocol) {
    case Tcp:
        return "TCP";
    case Udp:
        return "UDP";
    }

    m_errorOccurred = true;
    m_errorString = "Unknown protocol type " + QString::number(protocol);
    return QString();
}

/*!
    Checks up if error occurred in \a settings; if true - sets up error string according to
    \a settings error.
    \return true If there are no errors occurred in \a settings; otherwise returns true.
*/
bool QxWindowsFirewallSettings::checkSettingsStatus(const QSettings &settings)
{
    switch (settings.status()) {
    case QSettings::NoError:
        return true;
    case QSettings::AccessError:
        m_errorOccurred = true;
        m_errorString = "An access error occurred (e.g. trying to write to a read-only file).";
        return false;
    case QSettings::FormatError:
        m_errorOccurred = true;
        m_errorString = "A format error occurred (e.g. loading a malformed file).";
        return false;
    default:
        m_errorOccurred = true;
        m_errorString = "Unknown QSettings error: " + QString::number(settings.status());
        return false;
    }
}

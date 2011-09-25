#ifndef QXWINDOWSFIREWALLSETTINGS_H
#define QXWINDOWSFIREWALLSETTINGS_H

#include <QtCore/QString>
#include <QtCore/QUuid>

class QSettings;

class QxWindowsFirewallSettings
{
public:
    enum Protocol {
        Tcp,
        Udp
    };

public:
    QxWindowsFirewallSettings();

    static bool isOsSupported();
    bool createFirewallException(const QString &ruleName, const QUuid &uuid,
                                 const QString &appPath, const QString &description,
                                 Protocol protocol);
    bool createFirewallException(const QString &ruleName, Protocol protocol, int port);
    bool errorOccurred() const;
    QString errorString() const;

private:
    mutable bool m_errorOccurred;
    mutable QString m_errorString;

    int protocolNumber(Protocol protocol) const;
    QString protocolString(Protocol protocol) const;
    bool checkSettingsStatus(const QSettings &settings);
};

#endif // QXWINDOWSFIREWALLSETTINGS_H

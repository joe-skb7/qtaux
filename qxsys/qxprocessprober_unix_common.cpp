#include <QtCore/QProcess>
#include <QtCore/QRegExp>
#include "qxsys/qxprocessprober.h"

bool QxProcessProber::refreshProcessList(const QString &psCommand, const QString &pattern)
{
    m_processMap.clear();

    // Retrieving "ps" output
    QProcess psProcess;
    psProcess.start(psCommand, QIODevice::ReadOnly);
    if (!psProcess.waitForFinished()) {
        m_error = RetrieveError;
        m_errorString = psProcess.errorString();
        return false;
    }
    QList<QByteArray> processList = psProcess.readAll().split('\n');

    // Output processing
    if (processList.size() > 0)
        processList.removeAt(0); // removing table header
    processList.removeAll("");   // removing empty lines

    // Output validation
    if (processList.size() < 2) {
        QString processListString;
        for (int i = 0; i < processList.size(); ++i)
            processListString += processList.at(i) + "\n";
        processListString = processListString.trimmed();

        m_error = ValidationError;
        m_errorString = "Empty process list: " + processListString;
        return false;
    }

    // Output parsing
    QRegExp rx(pattern);
    int pos = 0;
    for (QList<QByteArray>::const_iterator it = processList.constBegin();
    it != processList.constEnd(); ++it) {
        pos = rx.indexIn(*it);
        if (pos == -1) {
            m_error = ParseError;
            m_errorString = "Failed to parse process line: " + *it;
            return false;
        }
        m_processMap[rx.cap(1).toInt()] = rx.cap(2);
    }

    m_processMap.remove(m_processMap.key(psCommand));

    return true;
}

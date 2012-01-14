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

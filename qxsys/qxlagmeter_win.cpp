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
#include <QtCore/QProcess>
#include <QtCore/QRegExp>
#include <QtCore/QTextCodec>
#include "qxsys/qxlagmeter.h"

QxLagMeter::QxLagMeter(QObject *parent)
    : QObject(parent), m_result(false)
{
    m_ping = new QProcess;
    QObject::connect(m_ping, SIGNAL(readyReadStandardOutput()),
                     this, SLOT(processOutput()));
    QObject::connect(m_ping, SIGNAL(finished(int)),
                     this, SLOT(processFinish()));
}

void QxLagMeter::ping(const QString &address)
{
    m_result = false;
    m_address = address;
    m_ping->start("ping", QStringList() << address);
}

/* private slots */

void QxLagMeter::processOutput()
{
    // Retrieving console output text
    QString text = QTextCodec::codecForName("cp-866")->toUnicode(m_ping->readAllStandardOutput());

    // Text processing
    text = text.replace("\r\n", "\n");
    text = text.trimmed();
    if (text.contains("\n\n")) {
        int index = text.indexOf("\n\n");
        text = text.left(index);
    }

    // Parsing
    QRegExp rx("^[^\\s]+.*:.*=\\s*\\d+.*([=<])\\s*(\\d+).*=\\s*\\d+.*$");
    rx.setMinimal(true);
    if (rx.indexIn(text, 0) != -1) {
        bool ok;
        int lag = rx.cap(2).toInt(&ok);

        QString sign = rx.cap(1);
        if (sign == "<" && lag == 1)
            lag = 0;

        if (!ok)
            return;
        m_result = true;
        m_ping->kill();
        emit lagReceived(lag);
    }
}

void QxLagMeter::processFinish()
{
    if (!m_result)
        emit lagReceived(-1);
}

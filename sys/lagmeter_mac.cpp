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

#include <QtCore/QLocale>
#include <QtCore/QProcess>
#include <QtCore/QRegExp>
#include "qaux/sys/lagmeter_mac.h"

/*!
    \todo Need to be tested.
*/

LagMeter::LagMeter(QObject *parent)
    : QObject(parent), m_result(false)
{
    m_ping = new QProcess;
    QObject::connect(m_ping, SIGNAL(readyReadStandardOutput()),
                     this, SLOT(processOutput()));
    QObject::connect(m_ping, SIGNAL(finished(int)),
                     this, SLOT(processFinish()));
}

void LagMeter::ping(const QString &address)
{
    m_result = false;
    m_address = address;
    m_ping->start("ping", QStringList() << "-c4" << address);
}

/* private slots */

void LagMeter::processOutput()
{
    QString text = m_ping->readAllStandardOutput();
    text = text.trimmed();

    // Parsing
    QRegExp rx("^.*:.*=\\s*\\d+.*=\\s*\\d+.*=\\s*([\\d\\.]+).*$");
    rx.setMinimal(true);
    if (rx.indexIn(text, 0) != -1) {
        bool ok;
        double floatLag = QLocale::c().toDouble(rx.cap(1), &ok);
        if (!ok)
            return;
        int lag = qRound(floatLag);
        m_result = true;
        m_ping->kill();
        emit lagReceived(lag);
    }
}

void LagMeter::processFinish()
{
    if (!m_result)
        emit lagReceived(-1);
}

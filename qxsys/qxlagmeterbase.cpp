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

#include "qxsys/qxlagmeterbase.h"

/*!
    \class QxLagMeter
    \brief Estimates "lag" - time for ping some IP or HTTP address.
    Since that class uses invoke of "ping" utility there is no root privileges required
    for ICMP.
    (see "man 2 chmod | grep SUID" command output for details).

    Simple example:
    \code
    void Test::exec()
    {
        QObject::connect(&m_lagMeter, SIGNAL(lagReceived(int)),
                         this, SLOT(processLag(int)));
        m_lagMeter.ping("8.8.8.8");
    }

    void Test::processLag(int ms)
    {
        qDebug() << "Lag: " << ms << " ms";
    }
    \endcode

    Another interesting example:
    \code
    void A::refreshServer(int index)
    {
        QxLagMeter *lagMeter;

        // Preserve repeated run of process
        if (m_lagMeterMap.contains(index)) {
            lagMeter = m_lagMeterMap[index];
            delete lagMeter;
        }

        lagMeter = new QxLagMeter;
        QObject::connect(lagMeter, SIGNAL(lagReceived(int)),
                         this, SLOT(processLag(int)));
        lagMeter->setId(index);
        m_lagMeterMap[index] = lagMeter;
        lagMeter->ping(someServerIpAddress);
    }

    void A::processLag(int msec)
    {
        QxLagMeter *lagMeter = static_cast<QxLagMeter*>(sender());
        int index = lagMeter->id();
        someServer.pingTime = msec;
    }
    \endcode
*/

/*!
    \class QxLagMeterBase
    \todo Write description...
*/

QxLagMeterBase::QxLagMeterBase()
    : m_id(-1)
{
}

/*!
    Sets up current lagmeter id.
*/
void QxLagMeterBase::setId(int id)
{
    m_id = id;
}

/*!
    Returns current lagmeter id.
*/
int QxLagMeterBase::id() const
{
    return m_id;
}

/*!
    Returns address for ping.
*/
QString QxLagMeterBase::address() const
{
    return m_address;
}

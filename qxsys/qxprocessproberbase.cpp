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

#include "qxsys/qxprocessproberbase.h"

/*!
    \class QxProcessProberBase
    \brief Base class for retrieving list of existing processes in system.
*/

/*!
    Returns list of existing processes.
*/
QStringList QxProcessProberBase::processList() const
{
    return m_processMap.values();
}

/*!
    Returns \a true if process with name \a name exists.
*/
bool QxProcessProberBase::exists(const QString &name) const
{
    for (QMap<int, QString>::const_iterator it = m_processMap.constBegin();
         it != m_processMap.constEnd(); ++it) {
        if (it.value() == name)
            return true;
    }
    return false;
}

/*!
    Returns \a true if process with identifier \a pid exists.
*/
bool QxProcessProberBase::exists(int pid) const
{
    return m_processMap.contains(pid);
}

/*!
    Returns type of last occurred error.
*/
QxProcessProberBase::Error QxProcessProberBase::error() const
{
    return m_error;
}

/*!
    Returns last occurred error in text representation.
*/
QString QxProcessProberBase::errorString() const
{
    return m_errorString;
}

/*!
    \fn bool refreshProcessList()
    Refreshes process list.
    \return true if process list refresed successfully.
*/

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

#include <time.h>
#include <QtCore/QObject>
#include "qxutil/qxtime.h"

/*!
    \class QxTime
    \brief Provides functions to work with time.
*/

/*!
    Makes string with estimated time (like "5 min 10 sec").
*/
QString QxTime::formatTime(time_t time)
{
    tm timeData = *gmtime(&time);
    // As time_t starts with 1970 year, but tm starts with 1900
    timeData.tm_year -= 70;
    // As time_t sets up day to Monday, not Sunday
    timeData.tm_mday -= 1;

    QString uptimeString;

    if (timeData.tm_yday > 0)
        uptimeString += QObject::tr("%n days", "", timeData.tm_yday);

    uptimeString = appendTrailingSpace(uptimeString);
    if (timeData.tm_hour > 0)
        uptimeString += QObject::tr("%n hours", "", timeData.tm_hour);

    uptimeString = appendTrailingSpace(uptimeString);
    if (timeData.tm_min > 0)
        uptimeString += QObject::tr("%n min", "", timeData.tm_min);

    uptimeString = appendTrailingSpace(uptimeString);
    if (uptimeString.isEmpty() || timeData.tm_sec > 0)
        uptimeString += QObject::tr("%n sec", "", timeData.tm_sec);

    uptimeString = uptimeString.simplified();

    return uptimeString;
}

/* private */

/*!
    Appends space in string \a string if it not empty.
*/
QString QxTime::appendTrailingSpace(const QString &string)
{
    if (string.isEmpty())
        return string;
    return string + " ";
}

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

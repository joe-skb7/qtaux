#ifndef QXCOMMON_H
#define QXCOMMON_H

/*!
    \file qxcommon.h
    \brief Contains common tools.
*/

/*!
    Calculates elements count in array \a a.
*/
#define NELEMS(a) ((int)(sizeof(a) / sizeof(a[0])))

#endif // QXCOMMON_H

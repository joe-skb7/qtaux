#ifndef QXPATHPROBER_H
#define QXPATHPROBER_H

#include <QtCore/QString>

/*!
    \class QxPathProber
    \brief Evaluates pathes for various system directories.
*/

class QxPathProber
{
public:
    QxPathProber() {}

    /*!
        Returns path for config directory of current user.
        \return Path or empty string if path probing failed.
    */
    static QString configDirPath();
};

#endif // QXPATHPROBER_H

#ifndef QXTIME_H
#define QXTIME_H

#include <QtCore/QDateTime>
#include <QtCore/QString>

class QxTime
{
public:
    static QString formatTime(time_t time);

private:
    static QString appendTrailingSpace(const QString &string);
};

#endif // QXTIME_H

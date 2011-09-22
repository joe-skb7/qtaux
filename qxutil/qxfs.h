#ifndef QXFS_H
#define QXFS_H

#include <QtCore/QString>

class QxFs
{
public:
    QxFs() {}

    static bool rmrf(const QString &dirPath);
};

#endif // QXFS_H

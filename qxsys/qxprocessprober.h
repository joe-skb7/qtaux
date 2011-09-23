#ifndef QXPROCESSPROBER_H
#define QXPROCESSPROBER_H

#include "qxsys/qxprocessproberbase.h"

/*!
    \class QxProcessProber
    \brief Provides convenient way to retrieve list of existing processes.
    \note \a refreshProcessList() must be called first.
*/

class QxProcessProber : public QxProcessProberBase
{
public:
    QxProcessProber() {}

    bool refreshProcessList();
#ifdef Q_OS_UNIX

private:
    bool refreshProcessList(const QString &psCommand, const QString &pattern);
#endif
};

#endif // QXPROCESSPROBER_H








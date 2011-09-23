#include <QtCore/QProcess>
#include <QtCore/QRegExp>
#include "qxsys/qxprocessprober.h"

bool QxProcessProber::refreshProcessList()
{
    return refreshProcessList("ps -e", "\\s*(\\d+).*\\d+:\\d+:\\d+\\s+(.*)\\s*");
}

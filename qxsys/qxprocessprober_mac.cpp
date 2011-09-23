#include <QtCore/QProcess>
#include <QtCore/QRegExp>
#include "qxsys/qxprocessprober.h"

bool QxProcessProber::refreshProcessList()
{
    return refreshProcessList("ps -A", "\\s*(\\d+)\\s+.*\\s+\\d+:\\d+.\\d+\\s+(.*)\\s*");
}

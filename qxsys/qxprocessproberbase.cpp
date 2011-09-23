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

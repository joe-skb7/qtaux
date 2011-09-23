#ifndef QXPROCESSPROBERBASE_H
#define QXPROCESSPROBERBASE_H

#include <QtCore/QMap>
#include <QtCore/QStringList>

class QxProcessProberBase
{
public:
    enum Error {
        NoError         = 0, //!< There are no errors.
        RetrieveError   = 1, //!< Error retrieving process list by system functions.
        ValidationError = 2, //!< Error validation of retrieved process list.
        ParseError      = 3  //!< Error parsing retrieved process list.
    };

public:
    QxProcessProberBase() {}
    virtual ~QxProcessProberBase() {}

    virtual bool refreshProcessList() = 0;
    QStringList processList() const;
    bool exists(const QString &name) const;
    bool exists(int pid) const;

    Error error() const;
    QString errorString() const;

protected:
    QMap<int, QString> m_processMap;
    Error m_error;
    QString m_errorString;
};

#endif // QXPROCESSPROBERBASE_H

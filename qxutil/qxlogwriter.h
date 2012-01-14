/****************************************************************************
**
** The code is licensed under the 2-clause, simplified BSD license.
**
** Copyright 2011 Sam Protsenko. All rights reserved.
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**
**   1. Redistributions of source code must retain the above copyright
**      notice, this list of conditions and the following disclaimer.
**
**   2. Redistributions in binary form must reproduce the above copyright
**      notice, this list of conditions and the following disclaimer in
**      the documentation and/or other materials provided with the
**      distribution.
**
** THIS SOFTWARE IS PROVIDED BY SAM PROTSENKO ''AS IS'' AND ANY
** EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
** IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
** PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL SAM PROTSENKO OR
** CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
** EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
** PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
** PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
** LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
** NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
** SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
** The views and conclusions contained in the software and documentation
** are those of the authors and should not be interpreted as representing
** official policies, either expressed or implied, of Sam Protsenko.
**
****************************************************************************/

#ifndef QXLOGWRITER_H
#define QXLOGWRITER_H

#include <QtCore/QMutex>
#include <QtCore/QObject>
#include <QtCore/QString>

class QxLogWriter;

QxLogWriter &qxAppLogger();

class QFile;

class QxLogWriter : public QObject
{
    Q_OBJECT

public:
    enum LogError {
        NoError = 0,        /*!< There are no errors occured */
        EmptyFilePathError, /*!< Empty file name */
        OpenError,          /*!< Opening file error */
        WriteError          /*!< File writing error; are you really first run startLogging()? */
    };

    enum HeaderFlag {
        NoHeader     = 0x0, /*!< Do not add header for message */
        TimeHeader   = 0x1, /*!< Adds logging time for every message */
        LevelHeader  = 0x2, /*!< Adds message level for every message */
        CustomHeader = 0x4  /*!< Adds user header for every message */
    };
    Q_DECLARE_FLAGS(Header, HeaderFlag)

public:
    explicit QxLogWriter(QObject *parent = 0);
    explicit QxLogWriter(const QString &filePath, QObject *parent = 0);
    ~QxLogWriter();

    bool startLogging();
    void endLogging();
    bool write(const QString &message, QtMsgType messageLevel = QtDebugMsg);
    void setLevel(QtMsgType level);
    QtMsgType level() const;
    LogError error() const;
    void setFilePath(const QString &filePath);
    QString filePath() const;
    void setHeader(Header header);
    Header header() const;
    void setCustomHeader(const QString &header);
    QString customHeader() const;

signals:
    void error(LogError newError);

private:
    void init();
    void setError(LogError error);
    QString levelString(QtMsgType level) const;

    static const char *LevelString[4];

    mutable QMutex m_mutex;
    QString m_filePath;
    QtMsgType m_loggerLevel;
    bool m_loggingStarted;
    LogError m_error;
    Header m_header;
    QString m_customHeader;
    QFile *m_file;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(QxLogWriter::Header)

#endif // QXLOGWRITER_H

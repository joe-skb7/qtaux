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

#include <QtCore/QDateTime>
#include <QtCore/QDebug>
#include <QtCore/QDir>
#include <QtCore/QFileInfo>
#include "qxutil/qxlogwriter.h"

/*!
    Returns singleton-object of QxLogWriter. It can be used as global singular logger object.
*/
QxLogWriter &qxAppLogger()
{
    static QxLogWriter logger;
    return logger;
}

/*!
    \class QxLogWriter
    \brief Provides simple logging functionality.
    \note This class is thread-safe.

    Example:
    \code
    QxLogWriter log;
    log.setFilePath(qApp->applicationDirPath() + "/log.dat");
    log.setHeader(QxLogWriter::TimeHeader | QxLogWriter::LevelHeader
                  | QxLogWriter::CustomHeader);
    log.setCustomHeader("{look it my log, my log is amazing!} ");
    log.write("first message");
    log.write("second message");
    \endcode
*/

/*!
    \enum QxLogWriter::LogError
    Error types that return by error() function.
*/

/*!
    \enum QxLogWriter::HeaderFlag
    Header flag types for adding auxiliary text in logged messages.
*/

/*!
    \fn void error(LogError newError)
    Emits when error ocured.
*/

const char *QxLogWriter::LevelString[4] = {
    "Debug",
    "Warning",
    "Critical",
    "Fatal"
};

/*!
    Inits class fields. Used by ctors.
*/
void QxLogWriter::init()
{
    m_loggerLevel = QtDebugMsg;
    m_loggingStarted = false;
    m_error = NoError;
    m_file = 0;
}

/*!
    Creates \a QxLogWriter object with parent \a parent.
*/
QxLogWriter::QxLogWriter(QObject *parent)
    : QObject(parent), m_mutex(QMutex::Recursive)
{
    init();
}

/*!
    Creates \a QxLogWriter object with parent \a parent and sets up path to log-file in \a filePath.
*/
QxLogWriter::QxLogWriter(const QString &filePath, QObject *parent)
    : QObject(parent), m_mutex(QMutex::Recursive), m_filePath(filePath)
{
    init();
}

/*!
    Destroys \a QxLogWriter object with saving of log-file.
*/
QxLogWriter::~QxLogWriter()
{
    endLogging();
}

/*!
    Opens file for logging.
    This function automatically invokes via \a write() method (if not be runned manually).
    \sa endLogging()
*/
bool QxLogWriter::startLogging()
{
    QMutexLocker locker(&m_mutex);

    if (m_loggingStarted)
        return true;

    if (m_filePath.isEmpty()) {
        setError(EmptyFilePathError);
        return false;
    }

    QFileInfo fileInfo(m_filePath);
    QDir logDir = fileInfo.dir();
    if (!logDir.exists())
        logDir.mkpath(logDir.path());

    if (!m_file)
        m_file = new QFile(m_filePath);

    if (!m_file->open(QIODevice::WriteOnly | QIODevice::Text)) {
        setError(OpenError);
        return false;
    }

    m_loggingStarted = true;

    return true;
}

/*!
    Closes log-file.
    This function automatically invokes via dtor.
    \sa startLogging()
*/
void QxLogWriter::endLogging()
{
    QMutexLocker locker(&m_mutex);

    m_loggingStarted = false;

    if (!m_file)
        return;
    m_file->close();
    delete m_file;
    m_file = 0;
}

/*!
    Writes \a message to log-file.
    \return false if error occured when attempt to write.
    \note Message can be not writed if \a messageLevel lower than level of logger object
    (see \a level() )
    \sa startLogging(), endLogging()
*/
bool QxLogWriter::write(const QString &message, QtMsgType messageLevel)
{
    QMutexLocker locker(&m_mutex);

    if (messageLevel < m_loggerLevel)
        return true;

    if (!m_loggingStarted && !startLogging())
        return false;

    if (!m_file) {
        qWarning() << "QxLogWriter::write() : unable to write; you have to run startLogging() "
                      "first";
        setError(WriteError);
        return false;
    }

    QTextStream out(m_file);
    out.seek(m_file->size());

    QString headerString;

    if (m_header.testFlag(TimeHeader))
        headerString.append("[" + QDateTime::currentDateTime().toString(Qt::ISODate) + "] ");
    if (m_header.testFlag(LevelHeader))
        headerString.append("<" + levelString(messageLevel) + "> ");
    if (m_header.testFlag(CustomHeader))
        headerString.append(m_customHeader);

    out << headerString << message << "\n";
    m_file->flush(); // forced flushing buffer into the file (protect against runtime errors)

    return true;
}

/*!
    Sets up level of logger. Messages with level lower than this level will not be written.
    \sa level()
*/
void QxLogWriter::setLevel(QtMsgType level)
{
    QMutexLocker locker(&m_mutex);

    if (m_loggerLevel != level)
        m_loggerLevel = level;
}

/*!
    Returns logger level.
    \sa setLevel()
*/
QtMsgType QxLogWriter::level() const
{
    QMutexLocker locker(&m_mutex);

    return m_loggerLevel;
}

/*!
    Returns type of last occurred error.
*/
QxLogWriter::LogError QxLogWriter::error() const
{
    QMutexLocker locker(&m_mutex);

    return m_error;
}

/*!
    Sets up path to log-file in \a filePath (file name must be included in path).
    If some directories in \a filePath don't exist - it will be created automatically.
*/
void QxLogWriter::setFilePath(const QString &filePath)
{
    QMutexLocker locker(&m_mutex);

    if (m_filePath != filePath)
        m_filePath = filePath;
}

/*!
    Returns setted path to log-file (with file name).
*/
QString QxLogWriter::filePath() const
{
    QMutexLocker locker(&m_mutex);

    return m_filePath;
}

/*!
    Sets up header type (that will be added to message).
    \sa setCustomHeader()
*/
void QxLogWriter::setHeader(Header header)
{
    QMutexLocker locker(&m_mutex);

    if (m_header ^ header)
        m_header = header;
}

/*!
    Returns header type (that will be added to message).
*/
QxLogWriter::Header QxLogWriter::header() const
{
    QMutexLocker locker(&m_mutex);

    return m_header;
}

/*!
    Sets up text of user header. User header will be used if QxLogWriter::CustomHeader is setted up.
    \sa setHeaderType()
*/
void QxLogWriter::setCustomHeader(const QString &header)
{
    QMutexLocker locker(&m_mutex);

    if (m_customHeader != header)
        m_customHeader = header;
}

/*!
    Returns text of user header.
    \sa headerType()
*/
QString QxLogWriter::customHeader() const
{
    QMutexLocker locker(&m_mutex);

    return m_customHeader;
}

/*!
    Sets up new type of last occured error and emits error signal.
*/
void QxLogWriter::setError(LogError newError)
{
    if (m_error != newError)
        m_error = newError;
    if (newError != NoError)
        emit error(m_error);
}

/*!
    Returns string representation for specified logging level.
*/
QString QxLogWriter::levelString(QtMsgType level) const
{
    switch (level) {
    case QtDebugMsg:
        return LevelString[0];
    case QtWarningMsg:
        return LevelString[1];
    case QtCriticalMsg:
        return LevelString[2];
    case QtFatalMsg:
        return LevelString[3];
    default:
        qWarning() << "QxLogWriter::levelString() : unknown level";
        return QString();
    }
}

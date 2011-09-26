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
** THIS SOFTWARE IS PROVIDED BY <COPYRIGHT HOLDER> ''AS IS'' AND ANY
** EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
** IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
** PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> OR
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

#ifndef QXSTARTUPPROVIDER_H
#define QXSTARTUPPROVIDER_H

#include <QtCore/QString>

/*!
    \class QxStartupProvider
    \brief Provides easy way to add application to startup list.

    \todo Write code for Linux and MacOs
    \todo http://lists.trolltech.com/qt-interest/2003-08/msg00985.html
    \todo http://stackoverflow.com/questions/4144222/running-a-qt-application-at-startup
*/

class QxStartupProvider
{
public:
    QxStartupProvider() {}

    /*!
        Returns execute path for application \a appName.
        If application \a appName is not in autorun section then empty string will be returned.
        \sa isAppRegistered()
    */
    static QString appStartFilePath(const QString &appName);
    /*!
        Returns \a true if application with name \a appName is contained in autorun section.
    */
    static bool isAppRegistered(const QString &appName);
    /*!
        Adds application \a appName to autorun section and sets \a filePath as executable
        file path.
        \sa removeApp()
    */
    static bool registerApp(const QString &appName, const QString &filePath);
    /*!
        Removes application \a appName from autorun section.
        \return true If application removed successfully or \a false if removing failed
        or if this application is not registered in autorun section.
        \sa isAppRegistered(), registerApp()
    */
    static bool removeApp(const QString &appName);
};

#endif // QXSTARTUPPROVIDER_H

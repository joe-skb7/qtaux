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

#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QtGui/QApplication>
#include <QtGui/QDesktopWidget>
#include <QtGui/QWidget>
#include "qxgui/qxgraphicsutil.h"

/*!
    \class QxGraphicsUtil
    \brief Contains functions for graphical isues.
*/

/*!
    Sets up qss style for widget \a widget from file \a fileName.
*/
bool QxGraphicsUtil::setStyleSheet(const QString &fileName, QWidget *widget)
{
    QFile file(fileName);
    if (file.open(QFile::ReadOnly)) {
        widget->setStyleSheet(QString::fromUtf8(file.readAll()));
    } else {
        qWarning() << __FILE__ << "," << __FUNCTION__ << "():" << "qss file \"" + fileName
                   + "\" not found!";
        return false;
    }
    return true;
}

/*!
    Sets up qss style for application \a app from file \a fileName .
*/
bool QxGraphicsUtil::setStyleSheet(const QString &fileName, QApplication *app)
{
    QFile file(fileName);
    if (file.open(QFile::ReadOnly)) {
        app->setStyleSheet(QString::fromUtf8(file.readAll()));
    } else {
        qWarning() << __FILE__ << "," << __FUNCTION__ << "():" << "qss file \"" + fileName
                   + "\" not found!";
        return false;
    }
    return true;
}

/*!
    Places window \a widget onto the screen center.
    \note Usage of this function recommended only for Windows, since the DE in other OS's
    able to arrange windows, so forced setting of window position is wrong behavior.
*/
void QxGraphicsUtil::moveWindowToCenter(QWidget *widget)
{
    QRect rect = widget->frameGeometry();
    rect.moveCenter(QDesktopWidget().availableGeometry().center());
    widget->move(rect.topLeft());
}

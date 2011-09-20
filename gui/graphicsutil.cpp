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
#include "gui/graphicsutil.h"

/*!
    \class GraphicsUtil
    \brief Содержит функции работы с графическими элементами.
*/

/*!
    Устанавливает qss-стиль из файла \a fileName для виджета \a widget.
*/
bool GraphicsUtil::setStyleSheet(const QString &fileName, QWidget *widget)
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
    Устанавливает qss-стиль из файла \a fileName для приложения \a app.
*/
bool GraphicsUtil::setStyleSheet(const QString &fileName, QApplication *app)
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
    Расположить окно по центру экрана.
    \note Использование этой функции рекомендуется только на Windows, т.к. в остальных ОС
    оконный менеджер сам знает, как лучше расположить окна и принудительная установка позиции
    окна является нежелательным поведением.
    \note http://www.wiki.crossplatform.ru/index.php/Как_расположить_окно_по_центру_экрана%3F
*/
void GraphicsUtil::moveWindowToCenter(QWidget *widget)
{
    QRect rect = widget->frameGeometry();
    rect.moveCenter(QDesktopWidget().availableGeometry().center());
    widget->move(rect.topLeft());
}

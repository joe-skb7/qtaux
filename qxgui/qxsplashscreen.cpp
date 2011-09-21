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
#include <QtGui/QPainter>
#include "qxgui/qxsplashscreen.h"

/*!
    \class QxSplashScreen
    \brief Splash screen with opacity support.
    \note This class is workaround for issue with QSplashScreen opacity; for details see:
    http://developer.qt.nokia.com/forums/viewthread/3155 .

    Example:
    \code
    QPixmap splashPixmap("/usr/share/kde4/apps/kscreensaver/kscience.png");
    QxSplashScreen *splash = new QxSplashScreen(splashPixmap);
    QFont font = splash->font();
    font.setPixelSize(10);
    splash->setFont(font);
    QRect messageRect(QPoint(10, 10), splashPixmap.rect().bottomRight());
    splash->setMessageRect(messageRect);
    splash->showMessage("Current version: 1.2.3", Qt::AlignLeft, Qt::white);
    QTimer::singleShot(2000, qApp, SLOT(quit()));
    splash->show();
    \endcode

    More simple example (from QSplashScreen doc):
    \code
        int main(int argc, char *argv[])
        {
            QApplication app(argc, argv);
            QPixmap pixmap("/usr/share/kde4/apps/kscreensaver/kscience.png");
            QxSplashScreen splash(pixmap);
            splash.show();
            app.processEvents();

            QWidget window;
            window.show();
            splash.finish(&window);
            return app.exec();
        }
    \endcode

    \sa QSplashScreen
*/

/*!
    Constructs splash screent with image \a pixmap.
*/
QxSplashScreen::QxSplashScreen(const QPixmap &pixmap)
    : QFrame(0, Qt::SplashScreen | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint)
{
    if (!pixmap.isNull()) {
        m_pixmap = pixmap;
    } else {
        qWarning() << "Pixmap for splash screen is null";
        return;
    }

    setAttribute(Qt::WA_TranslucentBackground);
    setFixedSize(m_pixmap.size());
}

/*!
    Clean message.
*/
void QxSplashScreen::clearMessage()
{
    m_message.clear();
    repaint();
}

/*!
    Sets up message rectangle sizes to \a rect.
    \param alignment Message text alignment.
    \sa showMessage()
*/
void QxSplashScreen::setMessageRect(QRect rect, int alignment)
{
    m_rect = rect;
    m_alignment = alignment;
}

/*!
    Indicates text \a message on splash screen.
    \param alignment Message text alignment.
    \param color Message text color.
    \sa setMessageRect(), finish()
*/
void QxSplashScreen::showMessage(const QString &message, int alignment, const QColor &color)
{
    m_message = message;
    m_alignment = alignment;
    m_color = color;
    repaint();
}

/*!
    Makes the splash screen wait until the widget \a win is displayed
    before calling close() on itself.
*/
void QxSplashScreen::finish(QWidget *win)
{
    if (win) {
#if defined(Q_WS_X11)
        extern void qt_x11_wait_for_window_manager(QWidget *win);
        qt_x11_wait_for_window_manager(win);
#endif
    }
    close();
}

/* protected */

void QxSplashScreen::mousePressEvent(QMouseEvent *)
{
    hide();
}

void QxSplashScreen::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(rect(), m_pixmap);
    painter.setPen(m_color);
    painter.drawText(m_rect, m_alignment, m_message);
}

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

#include <QtGui/QProxyStyle>
#include "ui_closedialog.h"
#include "qaux/gui/closedialog.h"
#ifdef Q_OS_WIN32
#include "qaux/gui/graphicsutil.h"
#endif

namespace {
    const int QuestionIconSize = 32;
} // anonymous namespace

/*!
    \class CloseDialog
    \brief Dialog with confirmation of closing.

    Example 1: modal dialog, i.e. synchronious invoke
    \code
    bool isAlwaysAskChecked;
    if (CloseDialog::askUser(this, m_appName, m_appName, &isAlwaysAskChecked)) {
        if (!isAlwaysAskChecked)
            emit closeDialogAlwaysAskChanged(false);
        qApp->quit();
    }
    \endcode

    Example 2: non-modal dialog,  i.t. asynchronious invoke (e.g. when invoking from tray)
    \code
    if (!m_isAskBeforeQuit) {
        qApp->quit();
        return;
    }

    static bool dialogVisible = false;

    if (dialogVisible && m_closeDialog) {
        m_closeDialog->activateWindow();
        m_closeDialog->setFocus();
        return;
    }

    if (!m_closeDialog) {
        m_closeDialog = new CloseDialog(this);
        m_closeDialog->setAppName(m_appName);
        m_closeDialog->setWindowTitle(m_appName);
    }

    dialogVisible = true;
    int ret = m_closeDialog->exec();
    if (ret == QDialog::Accepted) {
        if (!m_closeDialog->isAlwaysAskChecked())
            emit closeDialogAlwaysAskChanged(false);
        qApp->quit();
    }
    dialogVisible = false;
    \endcode
*/

/* public */

/*!
    Constructs dialog with parent \a parent.
*/
CloseDialog::CloseDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::CloseDialog)
{
    ui->setupUi(this);
#ifdef Q_OS_WIN32
    GraphicsUtil::setStyleSheet(":/qss/closedialog.qss", this);
#endif
    setupDialogIcon();
    setFixedSize(sizeHint());

    QObject::connect(ui->answerButtonBox, SIGNAL(accepted()),
                     this, SLOT(accept()));
    QObject::connect(ui->answerButtonBox, SIGNAL(rejected()),
                     this, SLOT(reject()));
}

/*!
    Destructor.
*/
CloseDialog::~CloseDialog()
{
    delete ui;
}

/*!
    Sets up name of application to \a name.
*/
void CloseDialog::setAppName(const QString &name)
{
    ui->questionLabel->setText(tr("Do you really want to exit %1?").arg(name));
    adjust();
}

/*!
    Sets up state of check box "Always perform ..." to \a isChecked.
*/
void CloseDialog::setAlwaysAskChecked(bool isChecked)
{
    ui->alwaysAskCheckBox->setChecked(isChecked);
}

/*!
    Returns state of check box "Always perform ...".
*/
bool CloseDialog::isAlwaysAskChecked() const
{
    return ui->alwaysAskCheckBox->isChecked();
}

/*!
    Shows close dialog and returns user action.
    \return true In case when user confirmed closing.
    \param title Dialog window title.
    \param appName Application name.
    \param isAlwaysAskChecked If given variable address - it will contain state of check box
           "Always perform...".
*/
bool CloseDialog::askUser(QWidget *parent, const QString &title, const QString &appName,
                          bool *isAlwaysAskChecked)
{
    CloseDialog dialog(parent);
    dialog.setWindowTitle(title);
    dialog.setAppName(appName);
    dialog.adjust();
    int ret = dialog.exec();
    if (isAlwaysAskChecked)
        *isAlwaysAskChecked = dialog.isAlwaysAskChecked();
    return ret;
}

/* protected */

void CloseDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

/* private */

/*!
    Sets up dialog icon.
*/
void CloseDialog::setupDialogIcon()
{
    ui->iconLabel->setText("");
    QIcon questionIcon = qApp->style()->standardIcon(QStyle::SP_MessageBoxQuestion);
    QPixmap questionPixmap = questionIcon.pixmap(QuestionIconSize);
    ui->iconLabel->setPixmap(questionPixmap);
    ui->iconLabel->resize(questionPixmap.size());
    adjust();
}

/*!
    Adjust window geometric sizes for changed widget sizes.
*/
void CloseDialog::adjust()
{
    ui->iconLabel->adjustSize();
    ui->questionLabel->adjustSize();
    ui->alwaysAskCheckBox->adjustSize();
    ui->questionPanelWidget->adjustSize();
    ui->answerPanelWidget->adjustSize();
    adjustSize();
}

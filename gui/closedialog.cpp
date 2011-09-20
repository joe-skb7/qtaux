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
#include "gui/closedialog.h"
#ifdef Q_OS_WIN32
#include "gui/graphicsutil.h"
#endif

namespace {
    const int QuestionIconSize = 32;
} // anonymous namespace

/*!
    \class CloseDialog
    \brief Диалог подтверждения закрытия приложения.

    Пример использования (в случае вызова из окна, которое после вызова станет модальным):
    \code
    bool isAlwaysAskChecked;
    if (CloseDialog::askUser(this, m_appName, m_appName, &isAlwaysAskChecked)) {
        if (!isAlwaysAskChecked)
            emit closeDialogAlwaysAskChanged(false);
        qApp->quit();
    }
    \endcode

    Пример использования (в случае вызова из трея):
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

CloseDialog::~CloseDialog()
{
    delete ui;
}

/*!
    Устанавливает имя приложения
*/
void CloseDialog::setAppName(const QString &name)
{
    ui->questionLabel->setText(tr("Do you really want to exit %1?").arg(name));
    adjust();
}

/*!
    Устанавливает состояние чек-бокса "Проверять всегда".
*/
void CloseDialog::setAlwaysAskChecked(bool isChecked)
{
    ui->alwaysAskCheckBox->setChecked(isChecked);
}

/*!
    Возвращает состояние чек-бокса "Проверять всегда".
*/
bool CloseDialog::isAlwaysAskChecked() const
{
    return ui->alwaysAskCheckBox->isChecked();
}

/*!
    Показывает диалог завершения приложения и возвращает ответ пользователя на вопрос о закрытии.
    \return true Если пользователь подтвердил завершение приложения.
    \param title Заголовок окна диалога.
    \param appName Имя закрываемого приложения.
    \param isAlwaysAskChecked Если передан адрес переменной - она будет содержать состояние
           чек-бокса "Проверять всегда".
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
    Устанавливает иконку диалога.
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
    Подстраивает геометрические размеры окна под измененные размеры виджетов.
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

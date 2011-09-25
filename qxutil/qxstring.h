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

#ifndef QXSTRING_H
#define QXSTRING_H

#include <QtCore/QLocale>
#include <QtCore/QString>

class QxString
{
public:
    QxString() {}

    /*!
        Converts float number \a num to string with precision \a prec.
        \note The purpose of this function is to truncate trailing zeros in fraction part;
        if you need to cenvert number to string - see QString::number().
        \sa stringFromDigit()
    */
    template <typename T> static QString stringFromFloat(T num, int prec = 2)
    {
        QChar lp = QLocale::system().decimalPoint();
        QChar cp = QLocale::c().decimalPoint();
        QString result = QString::number(num, 'f', prec);
        while ((result.contains(lp) || result.contains(cp))
               && (result.endsWith('0') || result.endsWith(lp) || result.endsWith(cp))) {
            result.chop(1);
        }
        return result;
    }

    /*!
        Converts number \a num to string.
        \return Result string or empty string if number \a num less or equal to \a cutDigit.
        Intended for truncate by value \a cutDigit
        (usually \a cutDigit is initialization value, e.g. -1).
        If you need to cenvert number to string - see QString::number().
        \sa stringFromFloat()
    */
    template <typename T> static QString stringFromDigit(T num, T cutNum, int prec = 2)
    {
        if (num <= cutNum)
            return QString();
        return stringFromFloat(num, prec);
    }

    static QString capacityString(quint64 bytes);
};

#endif // QXSTRING_H

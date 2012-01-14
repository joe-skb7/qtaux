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

#include "qxutil/qxstring.h"
#include "qxutil/qxcommon.h"

/*!
    \class QxString
    \brief Contains tools for work with strings.
*/

/*!
    Format the string with data capacity.
*/
QString QxString::capacityString(quint64 bytes)
{
    struct Suffix
    {
        const char *suf;
        quint64 size;
    };

    Suffix suffixes[] = {
        { "TiB", 1024ull*1024*1024*1024 },
        { "GiB", 1024ull*1024*1024 },
        { "MiB", 1024ull*1024 },
        { "KiB", 1024ull }
    };

    for (int i = 0; i < NELEMS(suffixes); ++i) {
        if (bytes >= suffixes[i].size) {
            return QString("%1 %2")
                    .arg(stringFromFloat((bytes * 1.0) / suffixes[i].size))
                    .arg(suffixes[i].suf);
        }
    }

    return QString("%1 B").arg(QString::number(bytes));
}
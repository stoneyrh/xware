/*
* ****************************************************************************
* *                                                                          *
* * Copyright 2008, xWorkshop Inc.                                           *
* * All rights reserved.                                                     *
* * Redistribution and use in source and binary forms, with or without       *
* * modification, are permitted provided that the following conditions are   *
* * met:                                                                     *
* *    * Redistributions of source code must retain the above copyright      *
* * notice, this list of conditions and the following disclaimer.            *
* *    * Redistributions in binary form must reproduce the above             *
* * copyright notice, this list of conditions and the following disclaimer   *
* * in the documentation and/or other materials provided with the            *
* * distribution.                                                            *
* *    * Neither the name of xWorkshop Inc. nor the names of its             *
* * contributors may be used to endorse or promote products derived from     *
* * this software without specific prior written permission.                 *
* * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS      *
* * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT        *
* * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR    *
* * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT     *
* * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,    *
* * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT         *
* * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,    *
* * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY    *
* * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT      *
* * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE    *
* * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.     *
* *                                                                          *
* * Author: stoneyrh@163.com                                                 *
* *                                                                          *
* ****************************************************************************
*/

#ifndef _X_LOCALE_H_
#define _X_LOCALE_H_

#include "xglobal.hxx"
#include <boost/locale.hpp>

namespace xws
{
namespace xlocale = boost::locale;
typedef xlocale::basic_format<xchar> xchar_format;

template<typename CharType>
xlocale::basic_message<CharType> xtr(CharType const *msg)
{
    return xlocale::translate(msg);
}

template<typename CharType>
xlocale::basic_message<CharType> xtr(CharType const *context, CharType const *msg)
{
    return xlocale::translate(context, msg);
}

template<typename CharType>
xlocale::basic_message<CharType> xtr(CharType const *single, CharType const *plural, int n)
{
    return xlocale::translate(single, plural, n);
}

template<typename CharType>
xlocale::basic_message<CharType> xtr(CharType const *context, CharType const *single, CharType const *plural, int n)
{
    return xlocale::translate(context, single, plural, n);
}

template<typename CharType>
xlocale::basic_message<CharType> xtr(std::basic_string<CharType> const &msg)
{
    return xlocale::translate(msg);
}

template<typename CharType>
xlocale::basic_message<CharType> xtr(std::basic_string<CharType> const &context, std::basic_string<CharType> const &msg)
{
    return xlocale::translate(context, msg);
}

template<typename CharType>
xlocale::basic_message<CharType> xtr(std::basic_string<CharType> const &context, std::basic_string<CharType> const &single, std::basic_string<CharType> const &plural, int n)
{
    return xlocale::translate(context, single, plural, n);
}

template<typename CharType>
xlocale::basic_message<CharType> xtr(std::basic_string<CharType> const &single, std::basic_string<CharType> const &plural, int n)
{
    return xlocale::translate(single, plural, n);
}

} // namespace xws

#endif

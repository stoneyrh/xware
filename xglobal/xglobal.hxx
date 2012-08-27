/*
* ****************************************************************************
* *                                                                          *
* * Copyright 2008, xWorkshop Inc.                                           *
* * All rights reserved.                                                     *
* * Redistribution and use in source and binary forms, with or without       *
* * modification, are permitted provided that the following conditions are   *
* * met:                                                                     *
* *    * Redistributions of source code must retain the above copyright     *
* * notice, this list of conditions and the following disclaimer.            *
* *    * Redistributions in binary form must reproduce the above             *
* * copyright notice, this list of conditions and the following disclaimer   *
* * in the documentation and/or other materials provided with the            *
* * distribution.                                                            *
* *    * Neither the name of xWorkshop Inc. nor the names of its             *
* * contributors may be used to endorse or promote products derived from     *
* * this software without specific prior written permission.                 *
* * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS     *
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

#ifndef _X_GLOBAL_H_
#define _X_GLOBAL_H_

#include <boost/cstdint.hpp> // for cstdint typedefs
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

#ifdef WINDOWS
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif // WIN32_LEAN_AND_MEAN
#endif // WINDOWS

namespace xws
{
// type of version number
typedef boost::uint16_t xversion_t;
// type of message id
typedef boost::uint16_t xmid_t;

typedef boost::uint8_t      xuint8_t;
typedef boost::uint16_t     xuint16_t;
typedef boost::uint32_t     xuint32_t;
typedef boost::uint64_t     xuint64_t;
typedef boost::int8_t       xint8_t;
typedef boost::int16_t      xint16_t;
typedef boost::int32_t      xint32_t;
typedef boost::int64_t      xint64_t;
typedef std::size_t         xsize_t;

#define INVALID_XMID        ((xmid_t)(-1))

typedef unsigned char       xbyte;
typedef xbyte*              xbyte_ptr;

#include <string>
#ifdef UNICODE
#define _X(x)               L##x
typedef wchar_t             xchar;
typedef std::wstring        xstring;
typedef std::wstringstream  xstringstream;
#define xcout               std::wcout
#define xcin                std::wcin
#define xcerr               std::wcerr
#else
#define _X(x)               x
typedef char                xchar;
typedef std::string         xstring;
typedef std::stringstream   xstringstream;
#define xcout               std::cout
#define xcin                std::cin
#define xcerr               std::cerr
#endif

// Always apply ansi string
#define _A(x)               x
#define acout               std::cout
#define acin                std::cin
#define acerr               std::cerr
typedef std::string         astring;
typedef std::stringstream   astringstream;
// Always apply unicode string
#define _U(x)               L##u
#define ucout               std::wcout
#define ucin                std::wcin
#define ucerr               std::wcerr
typedef std::wstring        ustring;
typedef std::wstringstream  ustringstream;

//
typedef std::vector<xstring>        xstring_list;
typedef std::vector<astring>        astring_list;
typedef std::vector<ustring>        ustring_list;

template <class Target, class Source>
struct match_str
{
    static Target apply(const Source& source)
    {
        Target target;
        target.assign(source.begin(), source.end());
        return target;
    }
};

template <class T>
struct match_str<T, T>
{
    static const T& apply(const T& s) { return s; }
};

template <class T>
void xunused(const T&) {}

}

#endif

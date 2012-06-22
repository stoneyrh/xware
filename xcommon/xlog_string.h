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

#ifndef _X_LOG_STRING_H_
#define _X_LOG_STRING_H_

#include "xglobal.h"
#include "xformat.h"
#include "xlocale.h"

namespace xws
{

class xlog_string
{
    public:
        /*
         * Construct an empty xlog_string
         */
        xlog_string();
        /*
         * Construct from a raw char string
         */
        xlog_string(const xchar *message);
        /*
         * Construct from a xstring
         */
        xlog_string(const xstring &message);
        /*
         * Construct from a xformat object
         */
        xlog_string(const xformat& format);
        /*
         * Construct from a xchar_format object
         */
        xlog_string(const xchar_format& format);
        /*
         * Copy constructor
         */
        xlog_string(const xlog_string &other);
        /*
         * Dextructor
         */
        ~xlog_string();
        /*
         * Return the message inside
         */
        xstring message() const { return message_; }
        /*
         * Convert to a xstring automatically
         */
        operator xstring () const { return message_; }
        /*
         * Compare with raw char string
         */
        bool operator == (const xchar *rhs) const;
        /*
         * Compare with xstring
         */
        bool operator == (const xstring &rhs) const;
        /*
         * Compare with another xlog_string
         */
        bool operator == (const xlog_string &rhs) const;
        /*
         * Assign from raw char string
         */
        xlog_string& operator = (const xchar *rhs);
        /*
         * Assign from xstring
         */
        xlog_string& operator = (const xstring &rhs);
        /*
         * Assign from another xlog_string
         */
        xlog_string& operator = (const xlog_string &rhs);
    private:
        xstring message_;
};

} // namespace xws

#endif

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

#include "xlog_message.h"

namespace xws
{

const xstring xlog_message::OUTPUT_FORMAT(_X("%1 - %2 - %3"));

xlog_message::xlog_message(xlog_level level, const xlog_string &message) : level_(level), message_(message), time_(xdate_time::current_date_time())
{
}

xlog_message::xlog_message(const xlog_message &other) : level_(other.level_), message_(other.message_), time_(other.time_)
{
}

xlog_message::~xlog_message()
{
}

xstring xlog_message::level_str() const
{
    switch (level_)
    {
        case LEVEL_DEBUG:
            return _X("DEBUG");
            break;
        case LEVEL_INFO:
            return _X("INFO");
            break;
        case LEVEL_WARN:
            return _X("WARN");
            break;
        case LEVEL_ERROR:
            return _X("ERROR");
            break;
        case LEVEL_FATAL:
            return _X("FATAL");
            break;
        default:
            break;
    }
    return _X("UNKNOWN");
}

xstring xlog_message::time_str() const
{
    return time_.x_str();
}

xlog_message& xlog_message::operator = (const xlog_message &rhs)
{
    if (this != &rhs)
    {
        level_ = rhs.level_;
        message_ = rhs.message_;
        time_ = rhs.time_;
    }
    return *this;
}

bool xlog_message::operator == (const xlog_message &rhs) const
{
    return level_ == rhs.level_ &&
           message_ == rhs.message_ &&
           time_ == rhs.time_;
}

xstring xlog_message::x_str() const
{
    return xstring();
}

} // namespace xws

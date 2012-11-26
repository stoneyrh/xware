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

#include "xlogger.hxx"
#include "xlog_message.hxx"

namespace xws
{

xlogger::xlogger() : level_(DEFAULT_LEVEL)
{
}

xlogger::~xlogger()
{
}

bool xlogger::configure(const xstring& /*config*/)
{
    return true;
}

xlog_level xlogger::level()
{
    boost::mutex::scoped_lock lock(mutex_);
    return level_;
}

void xlogger::set_level(xlog_level level)
{
    boost::mutex::scoped_lock lock(mutex_);
    level_ = level;
}

bool xlogger::add_appender(xlog_level level, const xlog_appender_ptr& appender)
{
    return false;
}

bool xlogger::remove_appender(xlog_level level, const xlog_appender_ptr& appender)
{
    return false;
}

void xlogger::reset()
{
}

void xlog_debug(const xlog_string &message)
{
    xcout << message.message() << std::endl;
}

void xlog_info(const xlog_string &message)
{
    xcout << message.message() << std::endl;
}

void xlog_warn(const xlog_string &message)
{
    xcout << message.message() << std::endl;
}

void xlog_error(const xlog_string &message)
{
    xcout << message.message() << std::endl;
}

void xlog_fatal(const xlog_string &message)
{
    xcout << message.message() << std::endl;
}

} // namespace xws

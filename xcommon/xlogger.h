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

#ifndef _X_LOGGER_H_
#define _X_LOGGER_H_

#include "xglobal.h"
#include "xlog_string.h"
#include "xlog_defs.h"
#include "xlog_appender.h"
#include <boost/thread.hpp>
#include <map>

// Use different default level for debug and release
#ifdef DEBUG
#define DEFAULT_LEVEL LEVEL_DEBUG
#else
#define DEFAULT_LEVEL LEVEL_INFO
#endif

namespace xws
{

class xlogger
{
    public:
        bool configure(const xstring& config);
        xlog_level level();
        void set_level(xlog_level level);
        bool add_appender(xlog_level level, const xlog_appender_ptr& appender);
        bool remove_appender(xlog_level level, const xlog_appender_ptr& appender);
        void reset();
    private:
        xlog_level level_;
        boost::mutex mutex_;
    private:
        xlogger();
        ~xlogger();
};

void xlog_debug(const xlog_string &message);
void xlog_info(const xlog_string &message);
void xlog_warn(const xlog_string &message);
void xlog_error(const xlog_string &message);
void xlog_fatal(const xlog_string &message);

#ifdef DEBUG
#define xdebug_info(str)        xlog_info(str)
#define xdebug_warn(str)        xlog_warn(str)
#define xdebug_error(str)       xlog_error(str)
#else
#define xdebug_info(str)
#define xdebug_warn(str)
#define xdebug_error(str)
#endif

} // namespace xws

#endif

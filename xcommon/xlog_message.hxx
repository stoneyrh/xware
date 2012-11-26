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

#ifndef _X_LOG_MESSAGE_H_
#define _X_LOG_MESSAGE_H_

#include "xlog_string.hxx"
#include "xdate_time.hxx"
#include "xlog_defs.hxx"
#include <boost/shared_ptr.hpp>

namespace xws
{

class xlog_message
{
    public:
        /*
         * This is the only way to construct a new xlog_message, which means level and message must be provided
         * When construction, the time will be set to current date time value
         */
        xlog_message(xlog_level level, const xlog_string &message);
        /*
         * Copy constructor
         */
        xlog_message(const xlog_message &other);
        /*
         * Desctructor
         */
        ~xlog_message();
        /*
         * Return xlog_level value
         */
        xlog_level level() const { return level_; }
        /*
         * Return the text representation of xlog_level
         */
        xstring level_str() const;
        /*
         * Return the time
         */
        xdate_time time() const { return time_; }
        /*
         * Set the time, this is only for unit test purpose
         */
        void time(const xdate_time &t) { time_ = t; }
        /*
         * Return the text representation of time
         */
        xstring time_str() const;
        /*
         * Return the message
         */
        xstring message() const { return message_; }
        /*
         * Assignment
         */
        xlog_message& operator = (const xlog_message &rhs);
        /*
         * Test equality
         */
        bool operator == (const xlog_message &rhs) const;
        /*
         * Convert all fields into a plain text string
         */
        xstring x_str() const;
    public:
        static const xstring OUTPUT_FORMAT;
    private:
        xlog_level level_;
        xlog_string message_;
        xdate_time time_;
};

typedef boost::shared_ptr<xlog_message> xlog_message_ptr;

} // namespace xws

#endif

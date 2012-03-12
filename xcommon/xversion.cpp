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

#include "xversion.h"
#include "xformat.h"

namespace xws
{

xversion::xversion(xversion_t major_value, xversion_t minor_value, xversion_t release_value, xversion_t build_value) :
    major_value_(major_value), minor_value_(minor_value), release_value_(release_value), build_value_(build_value)
{
}

xversion::xversion(const xversion& other) :
    major_value_(other.major_value_), minor_value_(other.minor_value_), release_value_(other.release_value_), build_value_(other.build_value_)
{
}

xversion::~xversion()
{
}

xversion& xversion::operator = (const xversion& rhs)
{
    if (this != &rhs)
    {
        major_value_ = rhs.major_value_;
        minor_value_ = rhs.minor_value_;
        release_value_ = rhs.release_value_;
        build_value_ = rhs.build_value_;
    }
    return *this;
}

bool xversion::operator == (const xversion& rhs) const
{
    return major_value_ == rhs.major_value_ &&
           minor_value_ == rhs.minor_value_ &&
           release_value_ == rhs.release_value_ &&
           build_value_ == rhs.build_value_;
}

xstring xversion::x_str() const
{
    xformat format(xformat(_X("%1%.%2%.%3%.%4%")) % major_value() %
           minor_value() % release_value() % build_value());
    return format.str();
}

} // namespace xws

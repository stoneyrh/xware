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

#ifndef _X_VERSION_H_
#define _X_VERSION_H_

#include "xglobal.hxx"

namespace xws
{

class xversion
{
    public:
        xversion(xversion_t major_value = 1, xversion_t minor_value = 0, xversion_t release_value = 0, xversion_t build_value = 0);
        xversion(const xversion& other);
        virtual ~xversion();

        xversion& operator = (const xversion& rhs);

        bool operator == (const xversion& rhs) const;

        xstring x_str() const;
        xversion_t major_value() const { return major_value_; }
        xversion_t minor_value() const { return minor_value_; }
        xversion_t release_value() const { return release_value_; }
        xversion_t build_value() const { return build_value_; }

        void set_major_value(xversion_t major_value) { major_value_ = major_value; }
        void set_minor_value(xversion_t minor_value) { minor_value_ = minor_value; }
        void set_release_value(xversion_t release_value) { release_value_ = release_value; }
        void set_build_value(xversion_t build_value) { build_value_ = build_value; }

        void set(xversion_t major_value, xversion_t minor_value, xversion_t release_value, xversion_t build_value)
        {
            major_value_ = major_value;
            minor_value_ = minor_value;
            release_value_ = release_value;
            build_value_ = build_value;
        }
    private:
        xversion_t major_value_;
        xversion_t minor_value_;
        xversion_t release_value_;
        xversion_t build_value_;
};

} // namespace xws

#endif

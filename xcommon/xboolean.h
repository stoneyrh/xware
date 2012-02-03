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

#ifndef _X_BOOLEAN_H_
#define _X_BOOLEAN_H_

#include "xmutex.h"

namespace xws
{

class xboolean
{
    public:
        xboolean(bool value = false) : value_(value) {}
        xboolean(const xboolean& other) : value_(other.value_) {}
        ~xboolean() {}

        xboolean& operator = (bool value)
        {
            xscoped_lock lock(mutex_);
            value_ = value;
            return *this;
        }

        xboolean& operator + (xboolean& rhs)
        {
            if (this != &rhs)
            {
                xscoped_lock lock(mutex_);
                value_ = (bool)rhs;
            }
            return *this;
        }

        operator bool ()
        {
            xscoped_lock lock(mutex_);
            return value_;
        }

        // Test if the value is false, if yes, then set it to be true
        // If the value is true, then nothing changed
        // Return the value before setting
        bool test_and_set()
        {
            xscoped_lock lock(mutex_);
            if (!value_)
            {
                value_ = true;
                return false;
            }
            return true;
        }
        // If the value is true, reset it to be false
        // If the value is false, then nothing changed
        // Return the value before setting
        bool test_and_reset()
        {
            xscoped_lock lock(mutex_);
            if (value_)
            {
                value_ = false;
                return true;
            }
            return false;
        }
    private:
        xboolean& operator = (const xboolean&);
    private:
        bool value_;
        xmutex mutex_;
};

} // namespace xws

#endif

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

#include "xbyte_array.hxx"
#include <string.h> // for memcpy

namespace xws
{

xbyte_array::xbyte_array()
{
}

xbyte_array::xbyte_array(const void* data, std::size_t size) : data_((xbyte_ptr)data, (xbyte_ptr)data + size)
{
}

xbyte_array::xbyte_array(const xbyte_array& other) : data_(other.data_)
{
}

xbyte_array::~xbyte_array()
{
}

xbyte_array xbyte_array::left(std::size_t number_of_bytes) const
{
    if (number_of_bytes >= size())
    {
        return *this;
    }
    return xbyte_array(data(), number_of_bytes);
}

xbyte_array xbyte_array::right(std::size_t number_of_bytes) const
{
    if (number_of_bytes >= size())
    {
        return *this;
    }
    return xbyte_array(data() + (size() - number_of_bytes), number_of_bytes);
}

xbyte_array& xbyte_array::operator += (const xbyte_array& rhs)
{
    data_.insert(data_.end(), rhs.data(), rhs.data() + rhs.size());
    return *this;
}

xbyte_array xbyte_array::operator + (const xbyte_array& rhs) const
{
    std::vector<xbyte> v(data_);
    v.insert(v.end(), rhs.data(), rhs.data() + rhs.size());
    return xbyte_array(&v[0], v.size());
}

xbyte_array& xbyte_array::operator = (const xbyte_array& rhs)
{
    if (this != &rhs)
    {
        data_ = rhs.data_;
    }
    return *this;
}

bool xbyte_array::operator == (const xbyte_array& rhs) const
{
    return data_ == rhs.data_;
}

bool xbyte_array::replace(xsize_t offset, void* data, xsize_t size)
{
    if (data && offset + size <= data_.size())
    {
        memcpy(this->data() + offset, data, size);
        return true;
    }
    return false;
}

}

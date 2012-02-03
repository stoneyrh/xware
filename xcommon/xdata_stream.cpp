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

#include "xdata_stream.h"

namespace xws
{

xdata_stream::xdata_stream() : good_(true)
{
}

xdata_stream::xdata_stream(const xbyte_array& byte_array) : good_(true)
{
    data_buffer_.set_data(byte_array);
}

xdata_stream::xdata_stream(xbyte_array* byte_array) : good_(true), data_buffer_(byte_array)
{
}

xdata_stream::~xdata_stream()
{
}

xdata_stream& xdata_stream::operator << (xint8_t value)
{
    good_ = data_buffer_.write(value) == sizeof(value);
    return *this;
}

xdata_stream& xdata_stream::operator << (xint16_t value)
{
    good_ = data_buffer_.write(value) == sizeof(value);
    return *this;
}

xdata_stream& xdata_stream::operator << (xint32_t value)
{
    good_ = data_buffer_.write(value) == sizeof(value);
    return *this;
}

xdata_stream& xdata_stream::operator << (xint64_t value)
{
    good_ = data_buffer_.write(value) == sizeof(value);
    return *this;
}

xdata_stream& xdata_stream::operator << (xuint8_t value)
{
    good_ = data_buffer_.write(value) == sizeof(value);
    return *this;
}

xdata_stream& xdata_stream::operator << (xuint16_t value)
{
    good_ = data_buffer_.write(value) == sizeof(value);
    return *this;
}

xdata_stream& xdata_stream::operator << (xuint32_t value)
{
    good_ = data_buffer_.write(value) == sizeof(value);
    return *this;
}

xdata_stream& xdata_stream::operator << (xuint64_t value)
{
    good_ = data_buffer_.write(value) == sizeof(value);
    return *this;
}

xdata_stream& xdata_stream::operator << (const std::string& value)
{
    good_ = data_buffer_.write(value) == (value.length() + 1) * sizeof(char);
    return *this;
}

xdata_stream& xdata_stream::operator << (const std::wstring& value)
{
    good_ = data_buffer_.write(value) == (value.length() + 1) * sizeof(wchar_t);
    return *this;
}

xdata_stream& xdata_stream::operator >> (xint8_t& value)
{
    good_ = data_buffer_.read(value) == sizeof(value);
    return *this;
}

xdata_stream& xdata_stream::operator >> (xint16_t& value)
{
    good_ = data_buffer_.read(value) == sizeof(value);
    return *this;
}

xdata_stream& xdata_stream::operator >> (xint32_t& value)
{
    good_ = data_buffer_.read(value) == sizeof(value);
    return *this;
}

xdata_stream& xdata_stream::operator >> (xint64_t& value)
{
    good_ = data_buffer_.read(value) == sizeof(value);
    return *this;
}

xdata_stream& xdata_stream::operator >> (xuint8_t& value)
{
    good_ = data_buffer_.read(value) == sizeof(value);
    return *this;
}

xdata_stream& xdata_stream::operator >> (xuint16_t& value)
{
    good_ = data_buffer_.read(value) == sizeof(value);
    return *this;
}

xdata_stream& xdata_stream::operator >> (xuint32_t& value)
{
    good_ = data_buffer_.read(value) == sizeof(value);
    return *this;
}

xdata_stream& xdata_stream::operator >> (xuint64_t& value)
{
    good_ = data_buffer_.read(value) == sizeof(value);
    return *this;
}

xdata_stream& xdata_stream::operator >> (std::string& value)
{
    xsize_t consumed_size = data_buffer_.read(value);
    good_ = consumed_size == (value.length() + 1) * sizeof(char);
    return *this;
}

xdata_stream& xdata_stream::operator >> (std::wstring& value)
{
    xsize_t consumed_size = data_buffer_.read(value);
    good_ = consumed_size == (value.length() + 1) * sizeof(wchar_t);
    return *this;
}

} // namespace xws

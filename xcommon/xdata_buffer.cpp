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

#include "xdata_buffer.hxx"
#include <string.h> // for memcpy

namespace xws
{

xdata_buffer::xdata_buffer() : byte_array_(&default_array_), current_offset_(0)
{
}

xdata_buffer::xdata_buffer(xbyte_array* byte_array) : byte_array_(byte_array), current_offset_(0)
{
}

xdata_buffer::~xdata_buffer()
{
}

void xdata_buffer::set_data(const xbyte_array& byte_array)
{
    default_array_ = byte_array;
    current_offset_ = 0;
}

void xdata_buffer::set_data(xbyte_ptr data, xsize_t size)
{
    default_array_ = xbyte_array(data, size);
    current_offset_ = 0;
}

xsize_t xdata_buffer::write(void* data, xsize_t size)
{
    if (data)
    {
        if (current_offset_ == byte_array_->size())
        {
            byte_array_->append((xbyte_ptr)data, size);
            current_offset_ += size;
            return size;
        }
        else
        {
            if (byte_array_->replace(current_offset_, data, size))
            {
                current_offset_ += size;
                return size;
            }
        }
    }
    return 0;
}

xsize_t xdata_buffer::read(void* data, xsize_t size)
{
    if (current_offset_ >= byte_array_->size())
    {
        return 0;
    }
    // If not enough data to read, then read all
    xsize_t gap = byte_array_->size() - current_offset_;
    size = size > gap ? gap : size;
    memcpy(data, byte_array_->data() + current_offset_, size);
    current_offset_ += size;
    return size;
}

xsize_t xdata_buffer::read(std::string& str)
{
    if (current_offset_ >= byte_array_->size())
    {
        return 0;
    }
    char* p = (char*)(byte_array_->data() + current_offset_);
    if (*p == '\0')
    {
        current_offset_ += sizeof(char);
        str.clear();
        return sizeof(char);
    }
    xsize_t rest_of_bytes = byte_array_->size() - current_offset_;
    xsize_t str_size = 0;
    char* e = p;
    while (*e != '\0' && str_size < rest_of_bytes) ++ e, str_size += sizeof(char);
    str = std::string(p, e);
    xsize_t consumed = str_size +
                       ((str_size < rest_of_bytes) ?
                            (*e == '\0' ? sizeof(char) : 0) :
                            0);
    current_offset_ += consumed;
    return consumed;
}

xsize_t xdata_buffer::read(std::wstring& str)
{
    if (current_offset_ >= byte_array_->size())
    {
        return 0;
    }
    wchar_t* p = (wchar_t*)(byte_array_->data() + current_offset_);
    if (*p == L'\0')
    {
        current_offset_ += sizeof(wchar_t);
        str.clear();
        return sizeof(wchar_t);
    }
    xsize_t rest_of_bytes = byte_array_->size() - current_offset_;
    xsize_t str_size = 0;
    wchar_t* e = p;
    while (*e != L'\0' && str_size < rest_of_bytes) ++ e, str_size += sizeof(wchar_t);
    str = std::wstring(p, e);
    xsize_t consumed = str_size +
                       ((str_size < rest_of_bytes) ?
                            (*e == L'\0' ? sizeof(wchar_t) : 0) :
                            0);
    current_offset_ += consumed;
    return consumed;
}

void xdata_buffer::seek(xint32_t offset, seek_where where)
{
    switch (where)
    {
        case seek_cur:
            current_offset_ += offset;
            break;
        case seek_end:
            current_offset_ = byte_array_->size() + offset;
            break;
        case seek_beg:
        default:
            current_offset_ = offset;
            break;
    }
}

} // namespace xws

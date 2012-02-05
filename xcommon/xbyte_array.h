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

#ifndef _X_BYTE_ARRAY_H_
#define _X_BYTE_ARRAY_H_

#include "xglobal.h"
#include <vector>

namespace xws
{

class xbyte_array
{
    public:
        xbyte_array();
        xbyte_array(const void* data, xsize_t size);
        xbyte_array(const xbyte_array& other);
        ~xbyte_array();

        xbyte_array left(xsize_t number_of_bytes) const;
        xbyte_array right(xsize_t number_of_bytes) const;
        void append(xint8_t value) { data_.insert(data_.end(), (xbyte_ptr)&value, (xbyte_ptr)&value + sizeof(value)); }
        void append(xint16_t value) { data_.insert(data_.end(), (xbyte_ptr)&value, (xbyte_ptr)&value + sizeof(value)); }
        void append(xint32_t value) { data_.insert(data_.end(), (xbyte_ptr)&value, (xbyte_ptr)&value + sizeof(value)); }
        void append(xint64_t value) { data_.insert(data_.end(), (xbyte_ptr)&value, (xbyte_ptr)&value + sizeof(value)); }
        void append(xuint8_t value) { data_.insert(data_.end(), (xbyte_ptr)&value, (xbyte_ptr)&value + sizeof(value)); }
        void append(xuint16_t value) { data_.insert(data_.end(), (xbyte_ptr)&value, (xbyte_ptr)&value + sizeof(value)); }
        void append(xuint32_t value) { data_.insert(data_.end(), (xbyte_ptr)&value, (xbyte_ptr)&value + sizeof(value)); }
        void append(xuint64_t value) { data_.insert(data_.end(), (xbyte_ptr)&value, (xbyte_ptr)&value + sizeof(value)); }
        void append(xbyte_ptr data, xsize_t size) { if (data) data_.insert(data_.end(), data, data + size); }
        void append(const std::string& str) { data_.insert(data_.end(), (xbyte_ptr)str.c_str(), (xbyte_ptr)str.c_str() + (str.length() + 1) * sizeof(char)); }
        void append(const std::wstring& str) { data_.insert(data_.end(), (xbyte_ptr)str.c_str(), (xbyte_ptr)str.c_str() + (str.length() + 1) * sizeof(wchar_t)); }

        bool replace(xsize_t offset, void* data, xsize_t size);

        template <class T>
        T value_at(xsize_t offset, const T& value = T())
        {
            T v(value);
            if (offset >= size() ||
                offset + sizeof(T) > size())
            {
                return v;
            }
            v = *(T*)(data() + offset);
            return v;
        }

        std::string str_at(xsize_t offset, xsize_t length, const std::string& value = std::string())
        {
            if (offset >= size() ||
                offset + length * sizeof(char) > size())
            {
                return value;
            }
            return std::string((char*)data() + offset, (char*)data() + offset + length);
        }

        std::wstring wstr_at(xsize_t offset, xsize_t length, const std::wstring& value = std::wstring())
        {
            if (offset >= size() ||
                offset + length * sizeof(wchar_t) > size())
            {
                return value;
            }
            return std::wstring((wchar_t*)(data() + offset), (wchar_t*)(data() + offset) + length);
        }

        xstring xstr_at(xsize_t offset, xsize_t length, const xstring& value = xstring())
        {
#ifdef UNICODE
            return wstr_at(offset, length, value);
#else
            return str_at(offset, length, value);
#endif
        }

        bool is_empty() const { return data_.empty(); }
        xsize_t size() const { return data_.size(); }
        xsize_t capacity() const { return data_.capacity(); }
        void reserve(xsize_t space) { data_.reserve(space); }
        const xbyte_ptr data() const { return (const xbyte_ptr)(&data_[0]); }
        void clear() { std::vector<xbyte> none; data_.swap(none); }

        xbyte_array& operator += (const xbyte_array& rhs);
        xbyte_array operator + (const xbyte_array& rhs) const;
        bool operator == (const xbyte_array& rhs) const;

        xbyte_array& operator = (const xbyte_array& rhs);
    private:
        std::vector<xbyte> data_;
};

}

#endif

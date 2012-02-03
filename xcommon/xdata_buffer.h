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

#ifndef _XDATA_BUFFER_H_
#define _XDATA_BUFFER_H_

#include "xio.h"
#include "xbyte_array.h"

namespace xws
{

class xdata_buffer
{
    public:
        xdata_buffer();
        xdata_buffer(xbyte_array* byte_array);
        ~xdata_buffer();

        void set_data(const xbyte_array& byte_array);
        void set_data(xbyte_ptr data, xsize_t size);
        xbyte_array byte_array() const { return *byte_array_; }
        xsize_t write(void* data, xsize_t size);
        xsize_t write(xint8_t value) { return write(&value, sizeof(value)); }
        xsize_t write(xint16_t value) { return write(&value, sizeof(value)); }
        xsize_t write(xint32_t value) { return write(&value, sizeof(value)); }
        xsize_t write(xint64_t value) { return write(&value, sizeof(value)); }
        xsize_t write(xuint8_t value) { return write(&value, sizeof(value)); }
        xsize_t write(xuint16_t value) { return write(&value, sizeof(value)); }
        xsize_t write(xuint32_t value) { return write(&value, sizeof(value)); }
        xsize_t write(xuint64_t value) { return write(&value, sizeof(value)); }
        // Write the end characters to indicate the end of string
        xsize_t write(const std::string& str)
        {
            // For empty string, we write an end character to indicate it is an empty string
            // So that when read out, we could tell now it is empty string
            return str.empty() ? write((void*)"\0", sizeof(char)) :
                                 write((void*)str.c_str(), (str.length() + 1) * sizeof(char));
        }
        xsize_t write(const std::wstring& str)
        {
            // For empty string, we write an end character to indicate it is an empty string
            // So that when read out, we could tell now it is empty string
            return str.empty() ? write((void*)L"\0", sizeof(wchar_t)) :
                                 write((void*)str.c_str(), (str.length() + 1) * sizeof(wchar_t));
        }
        xsize_t read(void* data, xsize_t size);
        xsize_t read(xint8_t& value) { return read(&value, sizeof(value)); }
        xsize_t read(xint16_t& value) { return read(&value, sizeof(value)); }
        xsize_t read(xint32_t& value) { return read(&value, sizeof(value)); }
        xsize_t read(xint64_t& value) { return read(&value, sizeof(value)); }
        xsize_t read(xuint8_t& value) { return read(&value, sizeof(value)); }
        xsize_t read(xuint16_t& value) { return read(&value, sizeof(value)); }
        xsize_t read(xuint32_t& value) { return read(&value, sizeof(value)); }
        xsize_t read(xuint64_t& value) { return read(&value, sizeof(value)); }
        xsize_t read(std::string& str);
        xsize_t read(std::wstring& str);
        xsize_t current_offset() const { return current_offset_; }
        void seek(xint32_t offset, seek_where where = seek_beg);

        bool at_end() const { return current_offset_ >= byte_array_->size(); }
    private:
        xbyte_array* byte_array_;
        xsize_t current_offset_;
        xbyte_array default_array_;
};

} // namespace xws

#endif

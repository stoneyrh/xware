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

#include <gtest/gtest.h>
#include "xdata_buffer.hxx"

using namespace xws;

void test_buffer(xdata_buffer& buffer)
{
    xint8_t xi8 = -8;
    xint16_t xi16 = -16;
    xint32_t xi32 = -32;
    xint64_t xi64 = -64;
    xuint8_t xui8 = 8;
    xuint16_t xui16 = 16;
    xuint32_t xui32 = 32;
    xuint64_t xui64 = 64;
    
    buffer.seek(0);
    xint8_t _xi8 = 0;
    xsize_t offset = 0;
    ASSERT_EQ(buffer.current_offset(), offset);
    ASSERT_EQ(buffer.read(&_xi8, sizeof(_xi8)), sizeof(_xi8));
    ASSERT_EQ(_xi8, xi8);
    offset += sizeof(_xi8);
    ASSERT_EQ(buffer.current_offset(), offset);
    xint16_t _xi16 = 0;
    ASSERT_EQ(buffer.read(&_xi16, sizeof(_xi16)), sizeof(_xi16));
    offset += sizeof(_xi16);
    ASSERT_EQ(_xi16, xi16);
    ASSERT_EQ(buffer.current_offset(), offset);
    xint32_t _xi32 = 0;
    ASSERT_EQ(buffer.read(&_xi32, sizeof(_xi32)), sizeof(_xi32));
    offset += sizeof(_xi32);
    ASSERT_EQ(_xi32, xi32);
    ASSERT_EQ(buffer.current_offset(), offset);
    xint64_t _xi64 = 0;
    ASSERT_EQ(buffer.read(&_xi64, sizeof(_xi64)), sizeof(_xi64));
    offset += sizeof(_xi64);
    ASSERT_EQ(_xi64, xi64);
    ASSERT_EQ(buffer.current_offset(), offset);
    xuint8_t _xui8 = 0;
    ASSERT_EQ(buffer.read(&_xui8, sizeof(_xui8)), sizeof(_xui8));
    ASSERT_EQ(_xui8, xui8);
    offset += sizeof(_xui8);
    ASSERT_EQ(buffer.current_offset(), offset);
    xuint16_t _xui16 = 0;
    ASSERT_EQ(buffer.read(&_xui16, sizeof(_xui16)), sizeof(_xui16));
    offset += sizeof(_xui16);
    ASSERT_EQ(_xui16, xui16);
    ASSERT_EQ(buffer.current_offset(), offset);
    xuint32_t _xui32 = 0;
    ASSERT_EQ(buffer.read(&_xui32, sizeof(_xui32)), sizeof(_xui32));
    offset += sizeof(_xui32);
    ASSERT_EQ(_xui32, xui32);
    ASSERT_EQ(buffer.current_offset(), offset);
    xuint64_t _xui64 = 0;
    ASSERT_EQ(buffer.read(&_xui64, sizeof(_xui64)), sizeof(_xui64));
    offset += sizeof(_xui64);
    ASSERT_EQ(_xui64, xui64);
    ASSERT_EQ(buffer.current_offset(), offset);
}

TEST(xdata_buffer_tests, test_init_with_byte_array_pointer)
{
    xbyte_array byte_array;
    xdata_buffer buffer(&byte_array);
    xint8_t xi8 = -8;
    xint16_t xi16 = -16;
    xint32_t xi32 = -32;
    xint64_t xi64 = -64;
    xuint8_t xui8 = 8;
    xuint16_t xui16 = 16;
    xuint32_t xui32 = 32;
    xuint64_t xui64 = 64;
    
    buffer.write(&xi8, sizeof(xi8));
    buffer.write(&xi16, sizeof(xi16));
    buffer.write(&xi32, sizeof(xi32));
    buffer.write(&xi64, sizeof(xi64));
    buffer.write(&xui8, sizeof(xui8));
    buffer.write(&xui16, sizeof(xui16));
    buffer.write(&xui32, sizeof(xui32));
    buffer.write(&xui64, sizeof(xui64));

    test_buffer(buffer);
}

TEST(xdata_buffer_tests, test_using_byte_array_with_set_byte_array)
{
    xbyte_array byte_array;
    xint8_t xi8 = -8;
    xint16_t xi16 = -16;
    xint32_t xi32 = -32;
    xint64_t xi64 = -64;
    xuint8_t xui8 = 8;
    xuint16_t xui16 = 16;
    xuint32_t xui32 = 32;
    xuint64_t xui64 = 64;
    byte_array.append(xi8);
    byte_array.append(xi16);
    byte_array.append(xi32);
    byte_array.append(xi64);
    byte_array.append(xui8);
    byte_array.append(xui16);
    byte_array.append(xui32);
    byte_array.append(xui64);
    
    xdata_buffer buffer;
    buffer.set_data(byte_array);
}

TEST(xdata_buffer_tests, test_using_byte_array_with_set_raw_data)
{
    xbyte_array byte_array;
    xint8_t xi8 = -8;
    xint16_t xi16 = -16;
    xint32_t xi32 = -32;
    xint64_t xi64 = -64;
    xuint8_t xui8 = 8;
    xuint16_t xui16 = 16;
    xuint32_t xui32 = 32;
    xuint64_t xui64 = 64;
    byte_array.append(xi8);
    byte_array.append(xi16);
    byte_array.append(xi32);
    byte_array.append(xi64);
    byte_array.append(xui8);
    byte_array.append(xui16);
    byte_array.append(xui32);
    byte_array.append(xui64);
    
    xdata_buffer buffer;
    buffer.set_data(byte_array.data(), byte_array.size());
}

TEST(xdata_buffer_tests, test_default_array)
{
    xdata_buffer buffer;
    xint8_t xi8 = -8;
    xint16_t xi16 = -16;
    xint32_t xi32 = -32;
    xint64_t xi64 = -64;
    xuint8_t xui8 = 8;
    xuint16_t xui16 = 16;
    xuint32_t xui32 = 32;
    xuint64_t xui64 = 64;
    
    buffer.write(&xi8, sizeof(xi8));
    buffer.write(&xi16, sizeof(xi16));
    buffer.write(&xi32, sizeof(xi32));
    buffer.write(&xi64, sizeof(xi64));
    buffer.write(&xui8, sizeof(xui8));
    buffer.write(&xui16, sizeof(xui16));
    buffer.write(&xui32, sizeof(xui32));
    buffer.write(&xui64, sizeof(xui64));
    test_buffer(buffer);
}

TEST(xdata_buffer_tests, test_read_and_write_std_string)
{
    std::string one("one");
    std::string two("two");
    std::string three("three");
    std::string millionare("millionare");
    std::string empty;
    xdata_buffer buffer;
    buffer.write(one);
    buffer.write(two);
    buffer.write(three);
    buffer.write(millionare);
    buffer.write(empty);
    buffer.write((void*)"abcde", 3 * sizeof(char));
    buffer.seek(0);
    std::string result;
    ASSERT_EQ(buffer.read(result), (one.length() + 1) * sizeof(char));
    ASSERT_EQ(result, one);
    ASSERT_EQ(buffer.read(result), (two.length() + 1) * sizeof(char));
    ASSERT_EQ(result, two);
    ASSERT_EQ(buffer.read(result), (three.length() + 1) * sizeof(char));
    ASSERT_EQ(result, three);
    ASSERT_EQ(buffer.read(result), (millionare.length() + 1) * sizeof(char));
    ASSERT_EQ(result, millionare);
    ASSERT_EQ(buffer.read(result), 1 * sizeof(char));
    ASSERT_TRUE(result.empty());
    // Only 3 characters, no ending char
    ASSERT_EQ(buffer.read(result), 3 * sizeof(char));
    ASSERT_EQ(result, std::string("abc"));
}

TEST(xdata_buffer_tests, test_read_and_write_std_wstring)
{
    std::wstring one(L"one");
    std::wstring two(L"two");
    std::wstring three(L"three");
    std::wstring millionare(L"millionare");
    std::wstring empty;
    xdata_buffer buffer;
    buffer.write(one);
    buffer.write(two);
    buffer.write(three);
    buffer.write(millionare);
    buffer.write(empty);
    buffer.write((void*)L"abcde", 3 * sizeof(wchar_t));
    buffer.seek(0);
    std::wstring result;
    ASSERT_EQ(buffer.read(result), (one.length() + 1) * sizeof(wchar_t));
    ASSERT_EQ(result, one);
    ASSERT_EQ(buffer.read(result), (two.length() + 1) * sizeof(wchar_t));
    ASSERT_EQ(result, two);
    ASSERT_EQ(buffer.read(result), (three.length() + 1) * sizeof(wchar_t));
    ASSERT_EQ(result, three);
    ASSERT_EQ(buffer.read(result), (millionare.length() + 1) * sizeof(wchar_t));
    ASSERT_EQ(result, millionare);
    ASSERT_EQ(buffer.read(result), 1 * sizeof(wchar_t));
    ASSERT_TRUE(result.empty());
    // Only 3 characters, no ending char
    ASSERT_EQ(buffer.read(result), 3 * sizeof(wchar_t));
    ASSERT_EQ(result, std::wstring(L"abc"));
}

TEST(xdata_buffer_tests, test_read_and_write_mix)
{
    xdata_buffer buffer;
    xint8_t xi8 = -8;
    xint16_t xi16 = -16;
    xint32_t xi32 = -32;
    xint64_t xi64 = -64;
    xuint8_t xui8 = 8;
    xuint16_t xui16 = 16;
    xuint32_t xui32 = 32;
    xuint64_t xui64 = 64;
    
    buffer.write(&xi8, sizeof(xi8));
    buffer.write(&xi16, sizeof(xi16));
    buffer.write(&xi32, sizeof(xi32));
    buffer.write(&xi64, sizeof(xi64));
    buffer.write(&xui8, sizeof(xui8));
    buffer.write(&xui16, sizeof(xui16));
    buffer.write(&xui32, sizeof(xui32));
    buffer.write(&xui64, sizeof(xui64));
    std::string one("one");
    std::wstring two(L"two");
    xstring xstr(_X("xstring"));
    buffer.write(one);
    buffer.write(two);
    buffer.write(xstr);

    test_buffer(buffer);
    std::string str_one;
    ASSERT_EQ(buffer.read(str_one), (one.length() + 1) * sizeof(char));
    ASSERT_EQ(one, str_one);
    std::wstring str_two;
    ASSERT_EQ(buffer.read(str_two), (two.length() + 1) * sizeof(wchar_t));
    ASSERT_EQ(two, str_two);
    xstring xstr_value;
    ASSERT_EQ(buffer.read(xstr_value), (xstr.length() + 1) * sizeof(xchar));
    ASSERT_EQ(xstr, xstr_value);
}

TEST(xdata_buffer_tests, test_seek)
{
    xdata_buffer buffer;
    xint32_t value = 0;
    ASSERT_EQ(buffer.current_offset(), 0);
    buffer.write(value);
    ASSERT_EQ(buffer.current_offset(), sizeof(value));
    buffer.seek(0, seek_end);
    ASSERT_EQ(buffer.current_offset(), sizeof(value));
    buffer.seek(0, seek_cur);
    ASSERT_EQ(buffer.current_offset(), sizeof(value));
    buffer.seek(0);
    ASSERT_EQ(buffer.current_offset(), 0);
    buffer.seek(0, seek_cur);
    ASSERT_EQ(buffer.current_offset(), 0);
    buffer.seek(0, seek_end);
    ASSERT_EQ(buffer.current_offset(), sizeof(value));
    xint32_t offset = sizeof(value);
    buffer.seek(-offset, seek_end);
    ASSERT_EQ(buffer.current_offset(), 0);
}

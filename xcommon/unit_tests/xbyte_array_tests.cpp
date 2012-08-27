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
#include "xbyte_array.hxx"

using namespace xws;

TEST(xbyte_array_tests, test_initialization_without_data)
{
    xbyte_array byte_array;
    EXPECT_TRUE(byte_array.is_empty());
    EXPECT_EQ(byte_array.size(), 0);
}

TEST(xbyte_array_tests, test_initialization_with_raw_data)
{
    xbyte bytes[] = "1234567890";
    std::size_t size = strlen((char*)bytes) * sizeof(xbyte);
    xbyte_array byte_array(bytes, size);
    EXPECT_FALSE(byte_array.is_empty());
    EXPECT_EQ(byte_array.size(), size);
    EXPECT_TRUE(memcmp(bytes, byte_array.data(), size) == 0);
}

TEST(xbyte_array_tests, test_copy_initialization)
{
    xbyte bytes[] = "1234567890";
    std::size_t size = strlen((char*)bytes) * sizeof(xbyte);
    xbyte_array byte_array(bytes, size);
    xbyte_array cloned(byte_array);
    EXPECT_EQ(byte_array, cloned);
}

TEST(xbyte_array_tests, test_function_left)
{
    xbyte bytes[] = "1234567890";
    std::size_t size = strlen((char*)bytes) * sizeof(xbyte);
    xbyte_array byte_array(bytes, size);
    xbyte_array left_3_bytes = byte_array.left(3);
    EXPECT_EQ(left_3_bytes.size(), 3);
    EXPECT_TRUE(memcmp(left_3_bytes.data(), "123", 3) == 0);

    xbyte_array equal_to_origin = byte_array.left(size);
    EXPECT_EQ(byte_array, equal_to_origin);

    xbyte_array a_new_copy = byte_array.left(size * 2);
    EXPECT_EQ(a_new_copy, byte_array);
}

TEST(xbyte_array_tests, test_function_right)
{
    xbyte bytes[] = "1234567890";
    std::size_t size = strlen((char*)bytes) * sizeof(xbyte);
    xbyte_array byte_array(bytes, size);
    xbyte_array right_3_bytes = byte_array.right(3);
    EXPECT_EQ(right_3_bytes.size(), 3);
    EXPECT_TRUE(memcmp(right_3_bytes.data(), "890", 3) == 0) << (char*)right_3_bytes.data();

    xbyte_array equal_to_origin = byte_array.right(size);
    EXPECT_EQ(equal_to_origin, byte_array);

    xbyte_array a_new_copy = byte_array.right(size * 2);
    EXPECT_EQ(a_new_copy, byte_array);
}

TEST(xbyte_array_tests, test_conjunction)
{
    xbyte bytes[] = "1234567890";
    std::size_t size = strlen((char*)bytes) * sizeof(xbyte);
    xbyte_array byte_array(bytes, size);
    xbyte_array left_5 = byte_array.left(5);
    xbyte_array rest = byte_array.right(size - 5);
    xbyte_array merged = left_5 + rest;
    EXPECT_EQ(merged, byte_array);
    left_5 += rest;
    EXPECT_EQ(left_5, merged);
}

TEST(xbyte_array_tests, test_assignment)
{
    xbyte bytes[] = "1234567890";
    std::size_t size = strlen((char*)bytes) * sizeof(xbyte);
    xbyte_array byte_array(bytes, size);
    xbyte_array array;
    array = byte_array;
    EXPECT_EQ(array, byte_array);
}

TEST(xbyte_array_tests, test_function_append)
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
    //
    xsize_t offset = 0;
    ASSERT_EQ(byte_array.value_at<xint8_t>(offset), xi8);
    offset += sizeof(xint8_t);
    ASSERT_EQ(byte_array.value_at<xint16_t>(offset), xi16);
    offset += sizeof(xint16_t);
    ASSERT_EQ(byte_array.value_at<xint32_t>(offset), xi32);
    offset += sizeof(xint32_t);
    ASSERT_EQ(byte_array.value_at<xint64_t>(offset), xi64);
    offset += sizeof(xint64_t);
    ASSERT_EQ(byte_array.value_at<xuint8_t>(offset), xui8);
    offset += sizeof(xuint8_t);
    ASSERT_EQ(byte_array.value_at<xuint16_t>(offset), xui16);
    offset += sizeof(xuint16_t);
    ASSERT_EQ(byte_array.value_at<xuint32_t>(offset), xui32);
    offset += sizeof(xuint32_t);
    ASSERT_EQ(byte_array.value_at<xuint64_t>(offset), xui64);
    offset += sizeof(xuint64_t);

    std::string ns("123");
    std::wstring ws(L"45678");
    byte_array.append(ns);
    byte_array.append(ws);
    ASSERT_EQ(byte_array.str_at(offset, ns.length()), ns);
    // Plus 1 to skip the _X('\0') char
    offset += (ns.length() + 1) * sizeof(char);
    ASSERT_EQ(byte_array.wstr_at(offset, ws.length()), ws);
    offset += (ws.length() + 1) * sizeof(wchar_t);

    xstring xs(_X("abcdefghijklmn"));
    byte_array.append(xs);
    ASSERT_EQ(byte_array.xstr_at(offset, xs.length()), xs);
    offset += (xs.length() + 1) * sizeof(xchar);

    xbyte_ptr raw = (xbyte_ptr)"khkl;,nko3jfkdsl";
    xsize_t size = strlen((char*)raw) * sizeof(xbyte);
    byte_array.append(raw, size);
    EXPECT_STREQ((char*)raw, byte_array.str_at(offset, size).c_str());
}

TEST(xbyte_array_tests, test_append_empty_string)
{
    xbyte_array byte_array;
    xstring empty;
    byte_array.append(empty);
    ASSERT_EQ(byte_array.size(), sizeof(xchar));
}

TEST(xbyte_array_tests, test_invalid_append)
{
    xbyte_array byte_array;
    xbyte_ptr p = 0;
    byte_array.append(p, 0);
    byte_array.append(p, 10);
}

TEST(xbyte_array_tests, test_function_replace)
{
    xbyte_array byte_array;
    xint16_t xi16 = -16;
    byte_array.append(xi16);
    ASSERT_FALSE(byte_array.replace(2 * sizeof(xi16), &xi16, sizeof(xi16)));
    ASSERT_FALSE(byte_array.replace(sizeof(xi16), &xi16, sizeof(xi16)));
    ASSERT_FALSE(byte_array.replace(sizeof(xi16) / 2, &xi16, sizeof(xi16)));
    ASSERT_FALSE(byte_array.replace(0, 0, 10));

    ASSERT_EQ(byte_array.value_at<xint16_t>(0), xi16);
    xint16_t _xi16 = 16;
    ASSERT_TRUE(byte_array.replace(0, &_xi16, sizeof(_xi16)));
    ASSERT_EQ(byte_array.value_at<xint16_t>(0), _xi16);
}

TEST(xbyte_array_tests, test_function_clear)
{
    xbyte_array byte_array;
    ASSERT_TRUE(byte_array.is_empty());
    xint16_t xi16 = -16;
    byte_array.append(xi16);
    ASSERT_FALSE(byte_array.is_empty());
    byte_array.clear();
    ASSERT_TRUE(byte_array.is_empty());
}

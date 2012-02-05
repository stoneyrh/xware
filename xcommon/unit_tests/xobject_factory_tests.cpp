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
#include "xobject_factory.h"

using namespace xws;

class xobject_facttory_testee {};

static xobject_facttory_testee object;
static xobject_facttory_testee* create_testee()
{
    return &object;
}

TEST(xobject_factory_tests, test_int_key)
{
    xobject_factory<xobject_facttory_testee> factory;
    ASSERT_TRUE(factory.register_creator(1, &create_testee));
    ASSERT_TRUE(factory.creator_of(1) != 0);
    ASSERT_FALSE(factory.creator_of(2));
    ASSERT_FALSE(factory.creator_of(12));
    xobject_facttory_testee* created = (factory.creator_of(1))();
    ASSERT_EQ(created, &object);
}

TEST(xobject_factory_tests, test_string_key)
{
    xobject_factory<xobject_facttory_testee, xstring> factory;
    ASSERT_TRUE(factory.register_creator(_X("xo"), &create_testee));
    ASSERT_TRUE(factory.creator_of(_X("xo")) != 0);
    ASSERT_FALSE(factory.creator_of(_X("ko")));
    ASSERT_FALSE(factory.creator_of(_X("vo")));
    xobject_facttory_testee* created = (factory.creator_of(_X("xo")))();
    ASSERT_EQ(created, &object);
}

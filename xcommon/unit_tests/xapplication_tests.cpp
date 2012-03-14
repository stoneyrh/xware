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
#include "xapplication.h"
#include "xprogram_options.h"
#include "xexception.h"

using namespace xws;

TEST(xapplication_tests, test_version_setter_getter)
{
    xchar* argv[] = {
        _X("app")
    };
    int argc = sizeof(argv);
    xapplication app(argc, argv);
    EXPECT_EQ(app.version().major_value(), 1);
    EXPECT_EQ(app.version().minor_value(), 0);
    EXPECT_EQ(app.version().release_value(), 0);
    EXPECT_EQ(app.version().build_value(), 0);
    app.set_version(1, 2, 3, 4);
    EXPECT_EQ(app.version().major_value(), 1);
    EXPECT_EQ(app.version().minor_value(), 2);
    EXPECT_EQ(app.version().release_value(), 3);
    EXPECT_EQ(app.version().build_value(), 4);
    EXPECT_EQ(app.version().x_str(), _X("1.2.3.4"));
}

TEST(xapplication_tests, test_option_operations)
{
    xprogram_options::options_description description(_A("app"));
    description.add_options()
        (_A("opta,a"), _A("option a"))
        (_A("optb,b"), xprogram_options::value<int>(), _A("option b"))
        (_A("optc,c"), xprogram_options::value<astring>(), _A("option c"))
        (_A("optd,d"), xprogram_options::value<int>()->default_value(20), _A("option d"))
        (_A("opte,e"), _A("option e"))
        (_A("optf,f"), _A("option f"))
        ;
    {
        xchar* argv[] = {
            _X("app"),
            _X("-a"),
            _X("-b"), _X("10")
        };
        int argc = sizeof(argv) / sizeof(argv[0]);
        xapplication app(argc, argv, description);
        EXPECT_TRUE(app.has_option(_A("opta")));
        EXPECT_TRUE(app.has_option(_A("optb")));
        EXPECT_EQ(app.option_value<int>(_A("optb")), 10);
        // An option with default value is always there
        EXPECT_TRUE(app.has_option(_A("optd")));
        EXPECT_FALSE(app.has_option(_A("optc")));
        EXPECT_FALSE(app.has_option(_A("opte")));
        EXPECT_FALSE(app.has_option(_A("optf")));
    }
    {
        xchar* argv[] = {
            _X("app"),
            _X("-c"), _X("Marry had a little lamp")
        };
        int argc = sizeof(argv) / sizeof(argv[0]);
        xapplication app(argc, argv, description);
        EXPECT_TRUE(app.has_option(_A("optc")));
        EXPECT_EQ(app.option_value<astring>(_A("optc")), _A("Marry had a little lamp"));
    }
    {
        xchar* argv[] = {
            _X("app"),
            _X("-c")
        };
        int argc = sizeof(argv) / sizeof(argv[0]);
        EXPECT_THROW(xapplication(argc, argv, description), xexception);
    }
}

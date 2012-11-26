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
#include "xnet_message.hxx"
#include "xnet_message_ids.hxx"

using namespace xws;

TEST(xnet_message_tests, test_message_ids)
{
    xnet_message_ids mids = xnet_message::net_message_ids();
    mids.name_to_id().clear();
    mids.name_to_id().insert(xnet_message_ids::name_to_id_t::value_type(_X("restart"), 1));
    mids.name_to_id().insert(xnet_message_ids::name_to_id_t::value_type(_X("stop"), 2));
    mids.name_to_id().insert(xnet_message_ids::name_to_id_t::value_type(_X("resume"), 3));
    mids.name_to_id().insert(xnet_message_ids::name_to_id_t::value_type(_X("pause"), 4));
    EXPECT_EQ(mids.name_to_id().size(), 4);
    EXPECT_EQ(mids.id_of(_X("restart")), 1);
    EXPECT_EQ(mids.id_of(_X("stop")), 2);
    EXPECT_EQ(mids.id_of(_X("resume")), 3);
    EXPECT_EQ(mids.id_of(_X("pause")), 4);
}

class common_message : public xnet_message
{
    public:
        void set_path_to_bin(const xstring& value) { path_to_bin_ = value; }
        void set_time(int value) { time_ = value; }

        xstring path_to_bin() const { return path_to_bin_; }
        int time() const { return time_; }
    protected:
        static void register_creator(const xstring& name, xnet_message_creator_t creator)
        {
            xnet_message_ids& mids = net_message_ids();
            mids.name_to_id().insert(xnet_message_ids::name_to_id_t::value_type(name, 1000));
            xnet_message::register_creator(name, creator);
        }
        virtual bool from_data_stream(xdata_stream& stream)
        {
            std::string path;
            stream >> path >> time_;
            path_to_bin_ = match_str<xstring, std::string>::apply(path);
            return stream.good();
        }
        virtual bool to_data_stream(xdata_stream& stream)
        {
            stream << match_str<std::string, xstring>::apply(path_to_bin_) << time_;
            return stream.good();
        }
    private:
        xstring path_to_bin_;
        int     time_;

        DECLARE_XNET_MESSAGE(common_message)
};

typedef xshared_ptr<common_message>::type common_message_ptr;

IMPLEMENT_XNET_MESSAGE(common_message)

TEST(xnet_message_tests, test_create_message_by_name)
{
    xnet_message_ptr source = xnet_message::create_message(_X("common_message"));
    EXPECT_TRUE(source);
    source = xnet_message::create_message(_X("bogus"));
    EXPECT_FALSE(source);
}

TEST(xnet_message_tests, test_create_message_by_id)
{
    xnet_message_ptr source = xnet_message::create_message(1000);
    EXPECT_TRUE(source);
    source = xnet_message::create_message(INVALID_XMID);
    EXPECT_FALSE(source);
}

TEST(xnet_message_tests, test_serialization)
{
    common_message_ptr source = xdynamic_pointer_cast<common_message>(xnet_message::create_message(_X("common_message")));
    EXPECT_TRUE(source);
    source->set_path_to_bin(_X("value of path_to_bin"));
    source->set_time(1234);
    xbyte_array byte_array;
    EXPECT_TRUE(source->to_byte_array(byte_array));
    EXPECT_TRUE(byte_array.size() > 0);
    xnet_message_set set = xnet_message::from_byte_array(byte_array);
    ASSERT_EQ(set.size(), 1);
    xnet_message_ptr dest = set.at(0);
    EXPECT_TRUE(dest);
    ASSERT_EQ(dest->id(), 1000);
}

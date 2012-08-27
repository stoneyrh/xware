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
#include "xnet_message_handler_manager.hxx"
#include "xnet_message_ids.hxx"

using namespace xws;

class manager_message : public xnet_message
{
    public:
    protected:
        static void register_creator(const xstring& name, xnet_message_creator_t creator)
        {
            xnet_message_ids& mids = net_message_ids();
            mids.name_to_id().insert(xnet_message_ids::name_to_id_t::value_type(name, 1001));
            xnet_message::register_creator(name, creator);
        }
        virtual bool to_data_stream(xdata_stream& stream)
        {
            return stream.good();
        }
        virtual bool from_data_stream(xdata_stream& stream)
        {
            return stream.good();
        }
        DECLARE_XNET_MESSAGE(manager_message)
};

IMPLEMENT_XNET_MESSAGE(manager_message)

class manager_handler : public xnet_message_handler
{
    public:
        manager_handler() : counter_(0) {}
        virtual void handle_message(xnet_message_ptr message, xnet_message_handler_context_ptr context = xnet_message_handler_context_ptr())
        {
            ++ counter_;
        }
        int counter_;
        DECLARE_XNET_MESSAGE_HANDLER(manager_handler)
};

typedef xshared_ptr<manager_handler>::type manager_handler_ptr;

IMPLEMENT_XNET_MESSAGE_HANDLER(manager_handler)

TEST(xnet_message_handler_manager_tests, test_functionality)
{
    xnet_message_handler_manager manager;
    ASSERT_FALSE(manager.connect(XNET_MESSAGE(x), XNET_MESSAGE_HANDLER(y)));
    ASSERT_TRUE(manager.connect(XNET_MESSAGE(manager_message), XNET_MESSAGE_HANDLER(manager_handler)));
    xnet_message_handler_ptr handler = manager.handler_of(1001);
    ASSERT_TRUE(handler);
    manager_handler_ptr mh = xdynamic_pointer_cast<manager_handler>(handler);
    ASSERT_TRUE(mh);
    ASSERT_EQ(mh->counter_, 0);
    xnet_message_ptr message = xnet_message::create_message(_X("manager_message"));
    handler->handle_message(message);
    ASSERT_EQ(mh->counter_, 1);
}

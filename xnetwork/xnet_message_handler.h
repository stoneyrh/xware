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

#ifndef _XNET_MESSAGE_HANDLER_H_
#define _XNET_MESSAGE_HANDLER_H_

#include "xnet_message.h"
#include "xsmart_ptr.h"
#include "xobject_factory.h"

#define DECLARE_XNET_MESSAGE_HANDLER(klass)              \
private:                                                 \
    static xnet_message_handler* create##klass()         \
    {                                                    \
        return new klass();                              \
    }                                                    \
    class klass##_register                               \
    {                                                    \
        public:                                          \
            klass##_register()                           \
            {                                            \
                xnet_message_handler::handler_factory(). \
                    register_creator(_X(#klass),         \
                        &klass::create##klass);          \
            }                                            \
    };                                                   \
private:                                                 \
    static klass##_register register_;                   \

//
#define IMPLEMENT_XNET_MESSAGE_HANDLER(klass)            \
    klass::klass##_register klass::register_;

namespace xws
{

class xnet_message_handler_context
{
    public:
        xnet_message_handler_context() {}
        virtual ~xnet_message_handler_context() {}

        /*
         * If accepted is true, then handshake success
         */
        virtual void handle_handshake_result(bool accepted) = 0;
        virtual void handle_heartbeat_result() = 0;
};

typedef xshared_ptr<xnet_message_handler_context>::type xnet_message_handler_context_ptr;

class xnet_message_handler;
typedef xobject_factory<xnet_message_handler, xstring> xnet_message_handler_factory;

class xnet_message_handler
{
    public:
        xnet_message_handler() {}
        virtual ~xnet_message_handler() {}

        virtual void handle_message(xnet_message_ptr message,
                        xnet_message_handler_context_ptr context = xnet_message_handler_context_ptr()) = 0;
        static xnet_message_handler_factory& handler_factory()
        {
            static xnet_message_handler_factory handler_factory;
            return handler_factory;
        }
};

typedef xshared_ptr<xnet_message_handler>::type xnet_message_handler_ptr;

} // namespace xws

#endif

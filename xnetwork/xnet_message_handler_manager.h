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

#ifndef _XNET_MESSAGE_HANDLER_MANAGER_H_
#define _XNET_MESSAGE_HANDLER_MANAGER_H_

#include <map>
#include "xnet_message_handler.h"
#include "xsmart_ptr.h"

namespace xws
{

#define XNET_MESSAGE(x)         _X(#x)
#define xNET_MESSAGE_HANDLER(x) _X(#x)

class xnet_message_handler_manager
{
    public:
        xnet_message_handler_manager();
        xnet_message_handler_manager(const xnet_message_handler_context_ptr context);
        ~xnet_message_handler_manager();

        void set_context(const xnet_message_handler_context_ptr context) { context_ = context; }
        xnet_message_handler_context_ptr context() const { return context_; }

        bool connect(const xstring& message, const xstring& handler);
        void handle_message_set(const xnet_message_set& set);
        xnet_message_handler_ptr handler_of(xmid_t mid) const;
    private:
        xnet_message_handler_context_ptr context_;
        typedef std::map<xmid_t, xnet_message_handler_ptr> message_to_handler_t;
        message_to_handler_t message_to_handler_;
};

typedef xshared_ptr<xnet_message_handler_manager>::type xnet_message_handler_manager_ptr;

} // namespace xws

#endif

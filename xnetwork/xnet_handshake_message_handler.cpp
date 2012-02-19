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

#include "xnet_handshake_message_handler.h"
#include "xnet_handshake_message.h"
#include "xassert.h"
#include "xlogger.h"

namespace xws
{

IMPLEMENT_XNET_MESSAGE_HANDLER(xnet_handshake_message_handler)

void xnet_handshake_message_handler::append_uuid(const xstring& uuid)
{
    try
    {
        xuuid_string_generator uuid_str_gen;
        xdebug_info(xformat(_X("Adding UUID \"%1%\" to acceptable UUID list.")) % uuid);
        acceptable_uuids().insert(uuid_str_gen(uuid));
    }
    catch (...)
    {
        xdebug_info(xformat(_X("Failed to add \"%1%\" to acceptable UUID list.")) % uuid);
    }
}

xnet_handshake_message_handler::xnet_handshake_message_handler()
{
}

xnet_handshake_message_handler::~xnet_handshake_message_handler()
{
}

void xnet_handshake_message_handler::handle_message(xnet_message_ptr message, xnet_message_handler_context_ptr context)
{
    xdebug_info(_X("Handling handshake message..."));
    xassert(message);
    xassert(context);
    // Call this only once since this should not change once initialized on startup
    static const xuuid_set& acceptable_uuids = xnet_handshake_message_handler::acceptable_uuids();
    xnet_handshake_message_ptr handshake_message = xdynamic_pointer_cast<xnet_handshake_message>(message);
    xassert(handshake_message);
    // If the UUID in the handshake message in the acceptable UUID set, then handshake accepted
    bool accepted = acceptable_uuids.find(handshake_message->uuid()) != acceptable_uuids.end();
    // If accept this handshake, first accept the heartbeat parameters
    if (accepted)
    {
        context->accept_heartbeat_params(handshake_message->heartbeat_interval(),
                                         handshake_message->heartbeat_threshold());
    }
    // Then handle the result
    context->handle_handshake_result(accepted);
}

}

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

#include "xnet_message_handler_manager.hxx"
#include "xnet_message.hxx"
#include "xnet_message_ids.hxx"
#include "xlogger.hxx"
#include "xlocale.hxx"

namespace xws
{

xnet_message_handler_manager::xnet_message_handler_manager()
{
}

xnet_message_handler_manager::xnet_message_handler_manager(const xnet_message_handler_context_ptr context) : context_(context)
{
}

xnet_message_handler_manager::xnet_message_handler_manager(const xnet_message_handler_manager& other) : context_(other.context_),
    message_to_handler_(other.message_to_handler_)
{
}

xnet_message_handler_manager::~xnet_message_handler_manager()
{
}

bool xnet_message_handler_manager::connect(const xstring& message, const xstring& handler)
{
    static const xnet_message_ids& mids = xnet_message::net_message_ids();
    xmid_t mid = mids.id_of(message);
    if (mid != INVALID_XMID)
    {
        static const xnet_message_handler_factory& factory = xnet_message_handler::handler_factory();
        if (factory.has_creator(handler))
        {
            xnet_message_handler_ptr h((factory.creator_of(handler))());
            xdebug_info(xchar_format(xtr(_X("Connecting message \"{1}\" with handler \"{2}\"..."))) % message % handler);
            message_to_handler_.insert(message_to_handler_t::value_type(mid, h));
            return true;
        }
        else
        {
            xdebug_info(xchar_format(xtr(_X("Handler \"{1}\" is not a registered handler."))) % handler);
        }
    }
    else
    {
        xdebug_info(xchar_format(xtr(_X("Message \"{1}\" is not a registered message."))) % message);
    }
    return false;
}

void xnet_message_handler_manager::handle_message_set(const xnet_message_set& set)
{
    for (xnet_message_set::const_iterator iter = set.begin(), end = set.end();
            iter != end; ++ iter)
    {
        xnet_message_handler_ptr handler = handler_of((*iter)->id());
        if (handler)
        {
            xdebug_info(xchar_format(xtr(_X("Handling message with id = {1}."))) % (*iter)->id());
            handler->handle_message(*iter, context());
        }
        else
        {
            xdebug_info(xchar_format(xtr(_X("There is no handler for handling message with id = {1}."))) % (*iter)->id());
        }
    }
}

xnet_message_handler_ptr xnet_message_handler_manager::handler_of(xmid_t mid) const
{
    message_to_handler_t::const_iterator pos = message_to_handler_.find(mid);
    if (pos != message_to_handler_.end())
    {
        return pos->second;
    }
    static xnet_message_handler_ptr none;
    return none;
}

xnet_message_handler_manager_ptr xnet_message_handler_manager::clone() const
{
    return xnet_message_handler_manager_ptr(new xnet_message_handler_manager(*this));
}

} // namespace xws

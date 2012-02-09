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

#include "xagent.h"
#include "xthread.h"
#include "xbind.h"
#include "xlogger.h"
#include "xnet_service_message_handler_context.h"

namespace xws
{
xagent::xagent() : io_service_(xthread::hardware_concurrency()), tcp_server_(io_service_),
    tcp_service_handler_manager_(new xnet_message_handler_manager())
{
    xdebug_info(_X("Creating xagent..."));
    //
    tcp_service_handler_manager_->connect(XNET_MESSAGE(xnet_handshake_message), XNET_MESSAGE_HANDLER(xnet_handshake_message_handler));
    tcp_service_handler_manager_->connect(XNET_MESSAGE(xnet_heartbeat_message), XNET_MESSAGE_HANDLER(xnet_heartbeat_message_handler));
    //
    tcp_server_.connection_established_sig().connect(xbind(&xagent::on_connection_established, this, _1));
}

xagent::~xagent()
{
    xdebug_info(_X("Deleting xagent..."));
}

int xagent::run()
{
    if (tcp_server_.start())
    {
        return io_service_.run();
    }
    return -1;
}

void xagent::on_connection_established(xtcp_io_object_ptr& io_object)
{
    xnet_service_ptr net_service(new xnet_service(io_object));
    net_service_manager_.add_service(net_service);
    net_service->net_service_stopped_sig().connect(xbind(&xnet_service_manager::remove_service, &net_service_manager_, _1));
    //
    xnet_message_handler_manager_ptr message_handler_manager = tcp_service_handler_manager_->clone();
    //
    xnet_service_message_handler_context_ptr context(new xnet_service_message_handler_context(net_service));
    message_handler_manager->set_context(context);
    //
    net_service->set_message_handler_manager(message_handler_manager);
    net_service->start();
}

void xagent::stop()
{
    io_service_.stop();
    net_service_manager_.stop_all_services();
}

bool xagent::on_ctrl_c()
{
    stop();
    return true;
}

bool xagent::on_ctrl_close()
{
    stop();
    return true;
}

bool xagent::on_ctrl_break()
{
    stop();
    return true;
}

bool xagent::on_ctrl_log_off()
{
    stop();
    return true;
}

bool xagent::on_ctrl_shutdown()
{
    stop();
    return true;
}

}

/*
* ****************************************************************************
* *                                                                          *
* * Copyright 2008, xWorkshop Inc.                                           *
* * All rights reserved.                                                     *
* * Redistribution and use in source and binary forms, with or without       *
* * modification, are permitted provided that the following conditions are   *
* * met:                                                                     *
* *    * Redistributions of source code must retain the above copyright      *
* * notice, this list of conditions and the following disclaimer.            *
* *    * Redistributions in binary form must reproduce the above             *
* * copyright notice, this list of conditions and the following disclaimer   *
* * in the documentation and/or other materials provided with the            *
* * distribution.                                                            *
* *    * Neither the name of xWorkshop Inc. nor the names of its             *
* * contributors may be used to endorse or promote products derived from     *
* * this software without specific prior written permission.                 *
* * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS      *
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

#include "xnet_tcp_client.h"
#include "xtcp_io_object.h"
#include "xbind.h"
#include "xlogger.h"

namespace xws
{

xnet_tcp_client::xnet_tcp_client(xio_service& io_service) : xnet_client(xtcp_io_object_ptr(new xtcp_io_object(io_service)))
{
    io_object_->connected_sig().connect(xbind(&xnet_tcp_client::on_connection_established, this));
    io_object_->connect_error_sig().connect(xbind(&xnet_tcp_client::on_connect_error, this, xplaceholders::error));
}

xnet_tcp_client::~xnet_tcp_client()
{
}

void xnet_tcp_client::connect_to(const xstring& host, xport_t port)
{
    xdebug_info(xformat(_X("Connecting to %1%:%2%...")) % host % port);
    io_object_->connect_to(host, port);
}

void xnet_tcp_client::on_connection_established()
{
    // Once connection established, send handshake immediately
    send_handshake();
    start_monitor_handshake();
}

void xnet_tcp_client::on_connect_error(const xerror_code& error_code)
{
}

void xnet_tcp_client::handshake_accepted()
{
    send_heartbeat();
    start_monitor_heartbeat();
}

void xnet_tcp_client::handshake_rejected()
{
}

void xnet_tcp_client::on_handshake_timeout(const xerror_code& error_code)
{
    if (error_code != xasio_error::operation_aborted)
    {
    }
}

void xnet_tcp_client::on_heartbeat_timeout(const xerror_code& error_code)
{
    if (error_code != xasio_error::operation_aborted)
    {
    }
}

void xnet_tcp_client::on_data_read(const xbyte_array& byte_array)
{
}

void xnet_tcp_client::on_data_read_error(const xerror_code& error_code)
{
}

} // namespace xws

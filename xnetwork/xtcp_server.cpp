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

#include "xtcp_server.h"
#include "xerror_code.h"
#include "xlogger.h"
#include "xformat.h"
#include "xbind.h"

namespace xws
{

xtcp_server::xtcp_server(xio_service& io_service) : io_service_(io_service), acceptor_(io_service)
{
    xdebug_info(_X("Creating xtcp_server..."));
}

xtcp_server::~xtcp_server()
{
    xdebug_info(_X("Deleting xtcp_server..."));
}

bool xtcp_server::start(const xtcp_endpoint& endpoint)
{
    xdebug_info((xformat(_X("Starting TCP server at endpoint (%1%:%2%)...")) %
            match_str<xstring, std::string>::apply(endpoint.address().to_string()) %
            endpoint.port()));
    xerror_code error_code;
    acceptor_.open(endpoint.protocol(), error_code);
    if (error_code)
    {
        xlog_error(xformat(_X("Failed to open acceptor with endpoint (%1%:%2%) with error \"%3%\".")) %
            match_str<xstring, std::string>::apply(endpoint.address().to_string()) %
            endpoint.port() %
            match_str<xstring, std::string>::apply(error_code.message()));
        return false;
    }
    //
    acceptor_.bind(endpoint, error_code);
    if (error_code)
    {
        xlog_error(xformat(_X("Failed to bind acceptor with endpoint (%1%:%2%) with error \"%3%\".")) %
            match_str<xstring, std::string>::apply(endpoint.address().to_string()) %
            endpoint.port() %
            match_str<xstring, std::string>::apply(error_code.message()));
        return false;
    }
    //
    acceptor_.listen(MAX_CONNECTIONS, error_code);
    if (error_code)
    {
        xlog_error(xformat(_X("Failed to listen to endpoint (%1%:%2%) with error \"%3%\".")) %
            match_str<xstring, std::string>::apply(endpoint.address().to_string()) %
            endpoint.port() %
            match_str<xstring, std::string>::apply(error_code.message()));
        return false;
    }
    start_accept();
    return true;
}

void xtcp_server::start_accept()
{
    xdebug_info(_X("Accepting connection..."));
    xtcp_io_object_ptr io_object(new xtcp_io_object(io_service()));
    acceptor_.async_accept(io_object->socket(),
            xbind(&xtcp_server::on_accept, this, io_object, xplaceholders::error));
}

void xtcp_server::on_accept(xtcp_io_object_ptr& io_object, const xerror_code& error_code)
{
    if (error_code)
    {
        xdebug_info((xformat(_X("Failed to accept connection with error \"%1%\".")) %
                match_str<xstring, std::string>::apply(error_code.message())));
        // TODO: What should be done here
    }
    else
    {
        xdebug_info((xformat(_X("Accepted one connection from (%1%:%2%).")) %
                match_str<xstring, std::string>::apply(io_object->peer_endpoint().address().to_string()) %
                io_object->peer_endpoint().port()));
        // Start next accept
        start_accept();
        // Issue the signal
        connection_established_sig_(io_object);
    }
}

}

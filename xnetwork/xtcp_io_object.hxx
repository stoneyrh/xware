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

#ifndef _X_TCP_IO_OBJECT_H_
#define _X_TCP_IO_OBJECT_H_

#include "xnet_io_object.hxx"

namespace xws
{

class xtcp_io_object : public xnet_io_object
{
    public:
        xtcp_io_object(xio_service& io_service);
        virtual ~xtcp_io_object();

        virtual void write(const xbyte_array_ptr& byte_array);
        virtual void read(xbyte_array& byte_array);
        virtual void start_async_read();
        virtual void connect_to(const xstring& host, xport_t port);
        virtual void do_async_write(const xbyte_array& byte_array);
        virtual void shutdown() { socket_.shutdown(xtcp_socket::shutdown_both); }
        virtual void cancel() { socket_.cancel(); }
        virtual void close() { socket_.close(); }
        virtual xio_service& io_service() { return socket_.get_io_service(); }

        xtcp_socket& socket() { return socket_; }
        const xtcp_socket& socket() const { return socket_; }
        xtcp_endpoint peer_endpoint() const { return socket_.remote_endpoint(); }
    protected:
        virtual void on_data_read(xbyte_ptr data, const xerror_code& error_code, xsize_t bytes_transferred);
        virtual void on_data_write(const xbyte_array_ptr& byte_array, const xerror_code& error_code, xsize_t bytes_transferred);
        virtual void on_connected(const xerror_code& error_code);
    private:
        xtcp_socket socket_;
};

typedef xshared_ptr<xtcp_io_object>::type xtcp_io_object_ptr;

}

#endif

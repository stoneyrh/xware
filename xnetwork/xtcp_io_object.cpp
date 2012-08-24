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

#include "xtcp_io_object.hxx"
#include "xlogger.hxx"
#include "xbind.hxx"
#include "xassert.hxx"
#include "xlocale.hxx"

namespace xws
{

xtcp_io_object::xtcp_io_object(xio_service& io_service) : socket_(io_service)
{
    xdebug_info(_X("Creating xtcp_io_object..."));
}

xtcp_io_object::~xtcp_io_object()
{
    xdebug_info(_X("Deleting xtcp_io_object..."));
}

void xtcp_io_object::write(const xbyte_array_ptr& byte_array)
{
    xassert(byte_array);
    socket_.async_send(xbuffer(byte_array->data(), byte_array->size()),
                xbind(&xtcp_io_object::on_data_write,
                       xdynamic_pointer_cast<xtcp_io_object>(shared_from_this()),
                       byte_array,
                       xplaceholders::error,
                       xplaceholders::bytes_transferred));
}

void xtcp_io_object::read(xbyte_array& byte_array)
{
}

void xtcp_io_object::start_async_read()
{
    xdebug_info(_X("Start asynchrous reading..."));
    xbyte_ptr buffer = read_buffer();
    socket_.async_read_some(xbuffer(buffer, READ_BUFFER_SIZE),
                xbind(&xtcp_io_object::on_data_read,
                       // Make sure use smart pointer
                       // Because if not, when the net service quit, the IO object may be deleted
                       // While the asynchrous operation is still in the queue, then it will corrupt
                       xdynamic_pointer_cast<xtcp_io_object>(shared_from_this()),
                       buffer,
                       xplaceholders::error,
                       xplaceholders::bytes_transferred));
}

void xtcp_io_object::do_async_write(const xbyte_array& byte_array)
{
}

void xtcp_io_object::on_data_read(xbyte_ptr buffer, const xerror_code& error_code, xsize_t bytes_transferred)
{
    if (error_code)
    {
        xdebug_info((xchar_format(xtr(_X("Failed to read data from xtcp_io_object with error \"{1}\"."))) %
                    match_str<xstring, std::string>::apply(error_code.message())));
        data_read_error_sig()(error_code);
        return;
    }
    xdebug_info((xchar_format(xtr(_X("{1} byte read from xtcp_io_object."), _X("{1} bytes read from xtcp_io_object."), bytes_transferred))
                % bytes_transferred));
    // Copy the buffer into byte array
    xbyte_array byte_array(buffer, bytes_transferred);
    //
    start_async_read();
    // Signal outside
    data_read_sig()(byte_array);
}

void xtcp_io_object::on_data_write(const xbyte_array_ptr& byte_array, const xerror_code& error_code, xsize_t bytes_transferred)
{
    if (error_code)
    {
        xdebug_info((xchar_format(xtr(_X("Failed to erite data to xtcp_io_object with error \"{1}\"."))) %
                    match_str<xstring, std::string>::apply(error_code.message())));
        data_write_error_sig()(error_code);
        return;
    }
    xdebug_info((xchar_format(xtr(_X("{1} byte written to xtcp_io_object."), _X("{1} bytes written to xtcp_io_object."), bytes_transferred))
                % bytes_transferred));
    //
    if (bytes_transferred != byte_array->size())
    {
        xdebug_error(xchar_format(xtr(_X("Not all bytes are transferred, expected = {1}, actual = {2}."))) % byte_array->size() % bytes_transferred);
    }
    data_write_sig()();
}

void xtcp_io_object::connect_to(const xstring& host, xport_t port)
{
    xaddress address = xaddress::from_string(match_str<std::string, xstring>::apply(host));
    xtcp_endpoint peer(address, port);
    socket_.async_connect(peer, xbind(&xtcp_io_object::on_connected,
                xdynamic_pointer_cast<xtcp_io_object>(shared_from_this()),
                xplaceholders::error));
}

void xtcp_io_object::on_connected(const xerror_code& error_code)
{
    if (error_code)
    {
        connect_error_sig()(error_code);
        return;
    }
    connected_sig()();
}

}

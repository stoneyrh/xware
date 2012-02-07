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

#ifndef _X_NETWORK_H_
#define _X_NETWORK_H_

#include <boost/asio.hpp>

namespace xws
{

typedef boost::asio::io_service               xio_service;
//
typedef boost::asio::ip::tcp::socket          xtcp_socket;
typedef boost::asio::ip::tcp::acceptor        xtcp_acceptor;
typedef boost::asio::ip::tcp::endpoint        xtcp_endpoint;
typedef boost::asio::ip::tcp::resolver        xtcp_resolver;
//
typedef boost::asio::ip::udp::socket          xudp_socket;
typedef boost::asio::ip::udp::endpoint        xudp_endpoint;
typedef boost::asio::ip::udp::resolver        xudp_resolver;
//
typedef boost::asio::ip::icmp::socket         xicmp_socket;
typedef boost::asio::ip::icmp::endpoint       xicmp_endpoint;
typedef boost::asio::ip::icmp::resolver       xicmp_resolver;
//
typedef boost::asio::ip::address              xaddress;
typedef boost::asio::ip::address_v4           xaddress_v4;
typedef boost::asio::ip::address_v6           xaddress_v6;

typedef boost::asio::deadline_timer           xdeadline_timer;
typedef boost::asio::mutable_buffer           xmutable_buffer;

typedef boost::asio::streambuf                xnet_streambuf;

#define xbuffer                               boost::asio::buffer
#define xbuffer_size                          boost::asio::buffer_size
#define xbuffer_cast                          boost::asio::buffer_cast

#define MAX_CONNECTIONS                       (boost::asio::socket_base::max_connections)

namespace xplaceholders = boost::asio::placeholders;

} // namespace xws

#endif

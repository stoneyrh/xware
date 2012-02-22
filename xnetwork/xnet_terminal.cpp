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

#include "xnet_terminal.h"
#include "xlogger.h"
#include "xassert.h"
#include "xbind.h"
#include "xposix_time.h"
#include "xnet_handshake_message.h"

#define HEARTBEAT_INTERVAL          1
#define HEARTBEAT_THRESHOLD         3

namespace xws
{

xnet_terminal::xnet_terminal(const xnet_io_object_ptr& io_object) :
    heartbeat_interval_(HEARTBEAT_INTERVAL),
    heartbeat_threshold_(HEARTBEAT_THRESHOLD),
    io_object_(io_object), deadline_timer_(io_object->io_service())
{
    xdebug_info(_X("Creating xnet_terminal..."));
}

xnet_terminal::xnet_terminal(const xnet_io_object_ptr& io_object,
        const xnet_message_handler_manager_ptr& handler_manager) :
            heartbeat_interval_(HEARTBEAT_INTERVAL),
            heartbeat_threshold_(HEARTBEAT_THRESHOLD),
            io_object_(io_object),
            deadline_timer_(io_object->io_service()),
            handler_manager_(handler_manager)
{
    xdebug_info(_X("Creating xnet_terminal..."));
}

xnet_terminal::~xnet_terminal()
{
    xdebug_info(_X("Deleting xnet_terminal..."));
}

void xnet_terminal::init_asynchrous_operation()
{
    xdebug_info(_X("Initializing asynchrous operation..."));
    // Note the order of connection
    data_read_error_conn_ = io_object_->data_read_error_sig().connect(xbind(&xnet_terminal::on_data_read_error, this, _1));
    data_read_conn_ = io_object_->data_read_sig().connect(xbind(&xnet_terminal::on_data_read, this, _1));
    data_write_error_conn_ = io_object_->data_write_error_sig().connect(xbind(&xnet_terminal::on_data_write_error, this, _1));
    data_write_conn_ = io_object_->data_write_sig().connect(xbind(&xnet_terminal::on_data_write, this));
}

void xnet_terminal::deinit_asynchrous_operation()
{
    xdebug_info(_X("Deinitializing asynchrous operation..."));
    // Reverse order as it is connected
    data_write_conn_.disconnect();
    data_write_error_conn_.disconnect();
    data_read_conn_.disconnect();
    data_read_error_conn_.disconnect();
}

void xnet_terminal::handle_byte_array(const xbyte_array& byte_array)
{
    xdebug_info(xformat(_X("Handling byte array with size = %1%...")) % byte_array.size());
    // unresolved_byte_array_ saves the data that not resolved last time
    unresolved_byte_array_ += byte_array;
    xsize_t recogized_size = 0;
    xnet_message_set set = xnet_message::from_byte_array(unresolved_byte_array_, &recogized_size);
    if (set.empty())
    {
        xassert(recogized_size == 0);
        xdebug_info(_X("The data received cannot be recoginzed, they will be abandoned."));
        unresolved_byte_array_.clear();
    }
    else
    {
        if (recogized_size == unresolved_byte_array_.size())
        {
            xdebug_info(_X("All data are recognized."));
            unresolved_byte_array_.clear();
        }
        else
        {
            unresolved_byte_array_ = unresolved_byte_array_.right(unresolved_byte_array_.size() - recogized_size);
            xdebug_info(xformat(_X("There are still %1% bytes not recognized.")) % unresolved_byte_array_.size());
        }
        // Handle all message immediately
        if (handler_manager_)
        {
            handler_manager_->handle_message_set(set);
        }
        else
        {
            xdebug_warn(_X("There is no handler associated with this service, message won't be handled!"));
        }
    }
}

void xnet_terminal::start_monitor_handshake(xsize_t seconds)
{
    xdebug_info(_X("Start monitoring handshake..."));
    deadline_timer_.expires_from_now(xposix_time::seconds(seconds));
    deadline_timer_.async_wait(xbind(&xnet_terminal::on_handshake_timeout, this, xplaceholders::error));
}

void xnet_terminal::end_monitor_handshake()
{
    xdebug_info(_X("Cancel monitoring handshake..."));
    deadline_timer_.cancel();
}

void xnet_terminal::start_monitor_heartbeat(xsize_t seconds)
{
    xdebug_info(_X("Start monitoring heartbeat..."));
    deadline_timer_.expires_from_now(xposix_time::seconds(seconds));
    deadline_timer_.async_wait(xbind(&xnet_terminal::on_heartbeat_timeout, this, xplaceholders::error));
}

void xnet_terminal::end_monitor_heartbeat()
{
    xdebug_info(_X("Cancel monitoring heartbeat..."));
    deadline_timer_.cancel();
}

void xnet_terminal::accept_heartbeat_params(xsize_t interval, xsize_t threshold)
{
    xdebug_info(xformat(_X("Accepting heartbeat parameters (interval = %1%, threshold = %2%)...")) % interval % threshold);
    heartbeat_interval_ = interval;
    heartbeat_threshold_ = threshold;
}

void xnet_terminal::send_heartbeat()
{
    xdebug_info(_X("Sending heartbeat..."));
    // We only need to create one, then later reuse it
    static xnet_message_ptr heartbeat_message = xnet_message::create_message(_X("xnet_heartbeat_message"));
    send(heartbeat_message);
}

void xnet_terminal::send_handshake(const xstring& uuid)
{
    xdebug_info(_X("Sending handshake..."));
    xnet_handshake_message_ptr handshake_message =
        xdynamic_pointer_cast<xnet_handshake_message>(
                xnet_message::create_message(_X("xnet_handshake_message")));
    //
    handshake_message->set_uuid(uuid);
    handshake_message->set_heartbeat_interval(heartbeat_interval_);
    handshake_message->set_heartbeat_threshold(heartbeat_threshold_);
    //
    send(handshake_message);
}

void xnet_terminal::send(const xnet_message_ptr& message)
{
    xassert(message);
    xbyte_array_ptr byte_array(new xbyte_array());
    if (message->to_byte_array(*byte_array.get()))
    {
        send(byte_array);
    }
    else
    {
        xdebug_info(_X("Failed to convert the message into byte array."));
    }
}

void xnet_terminal::send(const xbyte_array& byte_array)
{
    xassert(io_object_);
    io_object_->write(xbyte_array_ptr(new xbyte_array(byte_array)));
}

void xnet_terminal::send(const xbyte_array_ptr& byte_array)
{
    xassert(byte_array);
    io_object_->write(byte_array);
}

void xnet_terminal::on_data_write()
{
}

void xnet_terminal::on_data_write_error(const xerror_code& error_code)
{
}

void xnet_terminal::update_heartbeat()
{
    // Cancel the current handler, so that it won't expire
    end_monitor_heartbeat();
    // Start monitor heartbeat for next round
    start_monitor_heartbeat();
}

} // namespace xws

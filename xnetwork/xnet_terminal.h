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

#ifndef _XNET_TERMINAL_H_
#define _XNET_TERMINAL_H_

#include "xnetwork.h"
#include "xerror_code.h"
#include "xnet_message_handler_manager.h"
#include "xbyte_array.h"
#include "xnet_message.h"
#include "xnet_io_object.h"
#include "xsmart_ptr.h"

namespace xws
{

/*
 * xnet_termial is abstraction for each side of network communication
 * It encapsulates common used algorithms, and standard workflow for network programs
 */
class xnet_terminal : public xenable_shared_from_this<xnet_terminal>
{
    public:
        xnet_terminal(const xnet_io_object_ptr& io_object);
        xnet_terminal(const xnet_io_object_ptr& io_object, const xnet_message_handler_manager_ptr& handler_manager);
        virtual ~xnet_terminal();

        void set_message_handler_manager(const xnet_message_handler_manager_ptr& handler_manager) { handler_manager_ = handler_manager; }

        /*
         * These functions are for message_handler_context
         */
        virtual void handshake_accepted() = 0;
        virtual void handshake_rejected() = 0;
        virtual void accept_heartbeat_params(xsize_t interval, xsize_t threshold);
        virtual void send_heartbeat();
        //
        virtual void send(const xnet_message_ptr& message);
        virtual void send(const xbyte_array_ptr& byte_array);
        virtual void send(const xbyte_array& byte_array);
    protected:
        void init_asynchrous_operation();
        void deinit_asynchrous_operation();
        //
        virtual void handle_byte_array(const xbyte_array& byte_array);
        // Start monitoring hand shake message
        virtual void start_monitor_handshake(xsize_t seconds = 3);
        // If hand shake success within specified period, then end monitoring 
        virtual void end_monitor_handshake();
        virtual void on_handshake_timeout(const xerror_code& error_code) = 0;
        //
        virtual void on_data_read(xnet_io_object_ptr& io_object, const xbyte_array& byte_array) = 0;
        virtual void on_data_read_error(const xerror_code& error_code) = 0;
        virtual void on_data_write(xnet_io_object_ptr& io_object);
        virtual void on_data_write_error(const xerror_code& error_code);
    protected:
        xsize_t heartbeat_interval_;
        xsize_t heartbeat_threshold_;
        xnet_io_object_ptr io_object_;
        // This timer will be first used for monitoring handshake
        // After handshake success, it will be used for monitoring heartbeat
        xdeadline_timer deadline_timer_;
        xnet_message_handler_manager_ptr handler_manager_;
        // Save the data that not been recognized yet
        xbyte_array unresolved_byte_array_;
        // Signal connections
        xsig_connection data_read_conn_;
        xsig_connection data_read_error_conn_;
        xsig_connection data_write_conn_;
        xsig_connection data_write_error_conn_;
};

typedef xshared_ptr<xnet_terminal>::type xnet_terminal_ptr;

} // namespace xws

#endif

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

#ifndef _X_NET_SERVICE_H_
#define _X_NET_SERVICE_H_

#include "xnetwork.h"
#include "xsmart_ptr.h"
#include "xthread.h"
#include "xnet_io_object.h"
#include "xfunction.h"
#include "xsafe_queue.h"
#include "xsignal.h"
#include "xboolean.h"
#include "xnet_message_handler_manager.h"

namespace xws
{

typedef xfunction<void ()> net_command;
typedef xsafe_queue<net_command> net_command_list;

class xnet_service : public xenable_shared_from_this<xnet_service>
{
    public:
        typedef xshared_ptr<xnet_service>::type ptr_t;
        typedef xsignal<void (ptr_t&)> xnet_service_sig_t;
        //
        xnet_service(const xnet_io_object_ptr& io_object);
        ~xnet_service();

        void set_message_handler_manager(const xnet_message_handler_manager_ptr& handler_manager) { handler_manager_ = handler_manager; }

        void start();
        void stop();

        xnet_service_sig_t& net_service_started_sig() { return net_service_started_sig_; }
        xnet_service_sig_t& net_service_stopped_sig() { return net_service_stopped_sig_; }

    private:
        void run();
        void raise_stop_interruption();
        void on_data_read(xnet_io_object_ptr& io_object, const xbyte_array& byte_array);
        void on_error(const xerror_code& error_code);
        void handle_byte_array(const xbyte_array& byte_array);
        // Start monitoring hand shake message
        void start_monitor_handshake(xsize_t seconds = 3);
        // If hand shake success within specified period, then end monitoring 
        void end_monitor_handshake();
        void on_handshake_timeout(const xerror_code& error_code);
    private:
        //
        xnet_io_object_ptr io_object_;
        // This timer will be first used for monitoring handshake
        // After handshake success, it will be used for monitoring heartbeat
        xdeadline_timer deadline_timer_;
        xboolean is_running_;
        xnet_message_handler_manager_ptr handler_manager_;
        xbyte_array unresolved_byte_array_;
        net_command_list net_commands_;
        // Signals
        xnet_service_sig_t net_service_started_sig_;
        xnet_service_sig_t net_service_stopped_sig_;
};

typedef xnet_service::ptr_t xnet_service_ptr;

} // namespace xws

#endif

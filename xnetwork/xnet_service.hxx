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

#include "xnetwork.hxx"
#include "xsmart_ptr.hxx"
#include "xthread.hxx"
#include "xnet_io_object.hxx"
#include "xfunction.hxx"
#include "xthread_safe_queue.hxx"
#include "xsignal.hxx"
#include "xboolean.hxx"
#include "xnet_terminal.hxx"

namespace xws
{

typedef xfunction<void ()> net_command;
typedef xthread_safe_queue<net_command> net_command_list;

class xnet_service : public xnet_terminal
{
    public:
        typedef xshared_ptr<xnet_service>::type ptr_t;
        typedef xsignal<void (const ptr_t&)> xnet_service_sig_t;
        //
        xnet_service(const xnet_io_object_ptr& io_object);
        ~xnet_service();

        virtual void handshake_accepted() { send_handshake(); end_monitor_handshake();
                                            if (is_heartbeat_enabled()) start_monitor_heartbeat(); }
        virtual void handshake_rejected() { stop(); }

        virtual void start();
        virtual void stop();
        /*
         * Signal export
         */
        xnet_service_sig_t& net_service_started_sig() { return net_service_started_sig_; }
        xnet_service_sig_t& net_service_stopped_sig() { return net_service_stopped_sig_; }

    protected:
        virtual void on_handshake_timeout(const xerror_code& error_code);
        virtual void on_heartbeat_timeout(const xerror_code& error_code);
        virtual void on_data_read(const xbyte_array& byte_array);
        virtual void on_data_read_error(const xerror_code& error_code);
    private:
        void run();
        void raise_stop_interruption();
    private:
        xboolean is_running_;
        net_command_list net_commands_;
        // Signals
        xnet_service_sig_t net_service_started_sig_;
        xnet_service_sig_t net_service_stopped_sig_;
};

typedef xnet_service::ptr_t xnet_service_ptr;

} // namespace xws

#endif

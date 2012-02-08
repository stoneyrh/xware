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

#ifndef _X_AGENT_H_
#define _X_AGENT_H_

#include "xnetwork.h"
#include "xtcp_server.h"
#include "xtcp_io_object.h"
#include "xnet_service_manager.h"
#include "xnet_message_handler_manager.h"
#include "xconsole_event_listener.h"

namespace xws
{

class xagent : public xconsole_event_listener
{
    public:
        xagent();
        virtual ~xagent();
        xio_service& io_service() { return io_service_; }

        virtual int run();
        virtual void stop();

        /*
         * xconsole_event_listener
         */
        virtual bool on_ctrl_c();
        virtual bool on_ctrl_close();
        virtual bool on_ctrl_break();
        virtual bool on_ctrl_log_off();
        virtual bool on_ctrl_shutdown();
    private:
        void on_connection_established(xtcp_io_object_ptr& io_object);
    private:
        xio_service io_service_;
        xtcp_server tcp_server_;
        xnet_message_handler_manager_ptr tcp_service_handler_manager_;
        xnet_service_manager net_service_manager_;
};

} // namespace xws

#endif

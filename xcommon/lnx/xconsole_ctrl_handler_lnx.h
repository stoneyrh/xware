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

#ifndef _X_CONSOLE_CTRL_HANDLE_LNX_H_
#define _X_CONSOLE_CTRL_HANDLE_LNX_H_

#include "xconsole_event_listener.h"
#include "xlogger.h"
#include <errno.h>
#include <signal.h>

namespace xws
{

class xconsole_ctrl_handler_lnx
{
    public:
        static void create_console_handler(xconsole_event_listener* listener)
        {
            static xconsole_ctrl_handler_lnx handler(listener);
            xconsole_ctrl_handler_lnx::handler_ = &handler;
        }
    private:
        xconsole_ctrl_handler_lnx(xconsole_event_listener* listener) : listener_(listener)
        {
            struct sigaction action;
            memset(&action, 0, sizeof(action));
            action.sa_sigaction = &xconsole_ctrl_handler_lnx::handle_routine;
            action.sa_flags = SA_SIGINFO | SA_RESETHAND;
            int hookSignals[] = {SIGHUP, SIGINT, SIGKILL, SIGPIPE, SIGALRM, SIGTERM, SIGSTOP, SIGTSTP};
            for (size_t index = 0; index < sizeof(hookSignals) / sizeof(hookSignals[0]); ++ index)
            {
                int signal = hookSignals[index];
                if (sigaction(signal, &action, 0) != 0)
                {
                    xlog_error((xformat(_X("Installing action for signal = %1% (index = %2%) with error = \"%3%\".")) %
                                signal % index %
                                match_str<xstring, std::string>::apply(strerr(errno))));
                }
            }

        }
        ~xconsole_ctrl_handler_lnx()
        {
        }

        xconsole_event_listener* listener() { return listener_; }
        //
        static void handle_routine(int signal, siginfo_t* info, void* uap)
        {
            xunused(signal);
            xunused(info);
            xunused(uap);
            //
            xconsole_ctrl_handler_lnx::handler_->listener()->on_ctrl_c();
        }
    private:
        xconsole_event_listener* listener_;
        static xconsole_ctrl_handler_lnx* handler_;
};

}

#endif

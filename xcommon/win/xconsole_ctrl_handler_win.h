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

#ifndef _X_CONSOLE_CTRL_HANDLE_WIN_H_
#define _X_CONSOLE_CTRL_HANDLE_WIN_H_

#include <windows.h>
#include "xconsole_event_listener.h"
#include "xlogger.h"
#include "xlocale.h"

namespace xws
{

class xconsole_ctrl_handler_win
{
    public:
        xconsole_event_listener* listener() { return listener_; }

        static void create_console_handler(xconsole_event_listener* listener)
        {
            static xconsole_ctrl_handler_win handler(listener);
            xconsole_ctrl_handler_win::handler_ = &handler;
        }

        static BOOL WINAPI handler_routine(DWORD type)
        {
            switch (type)
            {
                case CTRL_C_EVENT:
                    return xconsole_ctrl_handler_win::handler_->listener()->on_ctrl_c();
                    break;
                case CTRL_BREAK_EVENT:
                    return xconsole_ctrl_handler_win::handler_->listener()->on_ctrl_break();
                    break;
                case CTRL_CLOSE_EVENT:
                    return xconsole_ctrl_handler_win::handler_->listener()->on_ctrl_close();
                    break;
                case CTRL_LOGOFF_EVENT:
                    return xconsole_ctrl_handler_win::handler_->listener()->on_ctrl_log_off();
                    break;
                case CTRL_SHUTDOWN_EVENT:
                    return xconsole_ctrl_handler_win::handler_->listener()->on_ctrl_shutdown();
                    break;
                default:
                    break;
            }
            return false;
        }
    private:
        xconsole_ctrl_handler_win(xconsole_event_listener* listener) : installed_(false), listener_(listener)
        {
            if (!SetConsoleCtrlHandler(xconsole_ctrl_handler_win::handler_routine, true))
            {
                xlog_error(xchar_format(xtr(_X("Failed to install console control handler with error code = {1}."))) % GetLastError());
            }
            else
            {
                installed_ = true;
            }
        }
        ~xconsole_ctrl_handler_win()
        {
            if (installed_)
            {
                if (!SetConsoleCtrlHandler(NULL, false))
                {
                    xlog_error(xchar_format(xtr(_X("Failed to remove console control handler with error code = {1}."))) % GetLastError());
                }
                else
                {
                    installed_ = false;
                }
            }
        }

    private:
        bool installed_;
        xconsole_event_listener* listener_;
        static xconsole_ctrl_handler_win* handler_;

};

} // namespace xws

#endif

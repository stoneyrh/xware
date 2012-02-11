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

#include "xcrash_handler_mac.h"
#include "xlogger.h"
#include "xdump_file_provider.h"
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <execinfo.h>
#include <Cocoa/Cocoa.h>

namespace xws
{

void uncaught_exception_handler(NSException* /*exception*/)
{
    xstring dumpFileName = GetDumpFileName();
    bool success = xcrash_handler_mac::dump_current_stack(dumpFileName);
}

xcrash_handler_mac::xcrash_handler_mac()
{
    NSSetUncaughtExceptionHandler(uncaught_exception_handler);
    //
    struct sigaction action;
    memset(&action, 0, sizeof(action));
    action.sa_sigaction = &xcrash_handler_mac::dump_handler;
    action.sa_flags = SA_SIGINFO | SA_RESETHAND;
    int hook_signals[] = {SIGSEGV, SIGBUS};
    for (size_t index = 0; index < sizeof(hook_signals) / sizeof(hook_signals[0]); ++ index)
    {
        int signal = hook_signals[index];
        if (sigaction(signal, &action, 0) != 0)
        {
            xstring error = match_str<xstring, std::string>::apply(strerror(errno));
            xlog_error(xformat(_X("Installing action for signal [%1%] with error \"%2%\".")) % signal % error);
        }
    }
}

xcrash_handler_mac::~xcrash_handler_mac()
{
}

void xcrash_handler_mac::dump_handler(int /*signal*/, siginfo_t* info, void* uap)
{
    if (info && uap)
    {
        xdump_file_provider dump_file_provider;
        xstring dump_to(dump_file_provider.dump_file_name());
        bool success = xcrash_handler_mac::dump_exception(info, uap, dump_to);
    }
}

bool xcrash_handler_mac::dump_exception(siginfo_t* info, void* uap, const xstring& to)
{
    if (info && uap)
    {
        return xcrash_handler_mac::dump_current_stack(to);
    }
    return false;
}

bool xcrash_handler_mac::dump_current_stack(const xstring& to)
{
    if (!to.empty())
    {
        int dump_file = open(match_str<std::string, xstring>::apply(to).c_str(), O_CREAT | O_WRONLY);
        if (dump_file != -1)
        {
            const int max_stack_size = 256;
            void* call_stack[max_stack_size];
            memset(call_stack, 0, sizeof(call_stack));
            int stackSize = backtrace(call_stack, max_stack_size);
            backtrace_symbols_fd(call_stack, stackSize, dump_file);
            close(dump_file);
            return true;
        }
    }
    return false;
}

} // namespace xws

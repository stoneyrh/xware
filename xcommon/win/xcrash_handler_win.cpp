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

#include "xcrash_handler_win.hxx"
#include "xdump_file_provider.hxx"
#include "xlogger.hxx"
#include "xlocale.hxx"

#pragma comment(lib, "dbghelp.lib")

namespace xws
{

xcrash_handler_win::xcrash_handler_win()
{
    SetUnhandledExceptionFilter(xcrash_handler_win::dump_handler);
}

xcrash_handler_win::~xcrash_handler_win()
{
}

LONG WINAPI xcrash_handler_win::dump_handler(__in struct _EXCEPTION_POINTERS* info)
{
    if (info)
    {
        xdump_file_provider dump_file_provider;
        xstring dump_to(dump_file_provider.dump_file_name());
        bool success = dump_exception(info, dump_to);
        return EXCEPTION_EXECUTE_HANDLER;
    }
    // Should never comes here
    return EXCEPTION_CONTINUE_SEARCH;
}

bool xcrash_handler_win::dump_exception(__in struct _EXCEPTION_POINTERS* info, const xstring& to)
{
    if (info && !to.empty())
    {
        HANDLE handle = CreateFile(to.c_str(), GENERIC_WRITE,
                0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (handle != INVALID_HANDLE_VALUE)
        {
            MINIDUMP_EXCEPTION_INFORMATION mei;
            ZeroMemory(&mei, sizeof(mei));
            mei.ThreadId = GetCurrentThreadId();
            mei.ExceptionPointers = info;

            MINIDUMP_CALLBACK_INFORMATION mci;
            ZeroMemory(&mci, sizeof(mci));
            mci.CallbackRoutine = xcrash_handler_win::mini_dump_callback;

            bool success = (bool)MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(),
                    handle, MiniDumpNormal, &mei, NULL, &mci);
            CloseHandle(handle);
            return success;
        }
        else
        {
            xlog_error(xchar_format(xtr(_X("Failed to create dump file \"{1}\"."))) % to);
        }
    }
    return false;
}

BOOL CALLBACK xcrash_handler_win::mini_dump_callback(PVOID, CONST PMINIDUMP_CALLBACK_INPUT, PMINIDUMP_CALLBACK_OUTPUT)
{
   return TRUE;
}

} // namespace xws

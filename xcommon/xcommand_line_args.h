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

#ifndef _X_COMMAND_LINE_ARGS_H_
#define _X_COMMAND_LINE_ARGS_H_

#include <string>
#include <cstring>

namespace xws
{
template <class T>
struct _str_helper;

template <>
struct _str_helper<char>
{
    static size_t length(const char* s) { return strlen(s); }
    static void copy(char* t, const char* s) { strcpy(t, s); }
};

template <>
struct _str_helper<wchar_t>
{
    static size_t length(const wchar_t* s) { return wcslen(s); }
    static void copy(wchar_t* t, const wchar_t* s) { wcscpy(t, s); }
};

template <class Target, class Source>
struct _converter
{
    static void apply(Target* t, Source* s)
    {
        std::basic_string<Source> src(s);
        std::basic_string<Target> dest(src.begin(), src.end());

        _str_helper<Target>::copy(t, dest.c_str());
    }
};

template <class T>
struct _converter<T, T>
{
    static void apply(T* t, T* s)
    {
        _str_helper<T>::copy(t, s);
    }
};

template <class Target, class Source>
class xcommand_line_args
{
    public:
        xcommand_line_args(int argc, Source* argv[]) : argc_(argc), argv_(0)
        {
            if (argc > 0 && argv)
            {
                argv_ = new Target*[argc];
                for (int i = 0; i < argc; ++ i)
                {
                    size_t len = _str_helper<Source>::length(argv[i]);
                    argv_[i] = new Target[len + 1];
                    memset((char*)argv_[i], 0, (len + 1) * sizeof(Target));
                    _converter<Target, Source>::apply(argv_[i], argv[i]);
                }
            }
        }
        // This will pass the ownership of argv_ from other to this
        xcommand_line_args(const xcommand_line_args<Target, Source>& other) : argc_(other.argc_), argv_(other.argv_)
        {
            // Invalid the other
            //other.argc_ = 0;
            //other.argv_ = 0;
        }
        ~xcommand_line_args()
        {
            if (argc_ > 0 && argv_)
            {
                for (int i = 0; i < argc_; ++ i)
                {
                    delete []argv_[i];
                }
                delete []argv_;
            }
        }

        // Do not save the reference of the returned value
        operator Target** ()
        {
            return argv_;
        }
    private:
        // Disable assignment
        xcommand_line_args<Target, Source>& operator = (const xcommand_line_args<Target, Source>& rhs);
    private:
        int argc_;
        Target** argv_;
};

template <class T>
class xcommand_line_args<T, T>
{
    public:
        xcommand_line_args(int, T* argv[]) : argv_(argv) {}
        xcommand_line_args(const xcommand_line_args<T, T>& other) : argv_(other.argv_) {}
        ~xcommand_line_args() {}

        operator T** ()
        {
            return argv_;
        }
    private:
        // Disable assignment
        xcommand_line_args<T, T>& operator = (const xcommand_line_args<T, T>& rhs);
    private:
        T** argv_;
};

template <class Target, class Source>
xcommand_line_args<Target, Source> xargs(int argc, Source** argv)
{
    return xcommand_line_args<Target, Source>(argc, argv);
}
} // namespace xws

#endif

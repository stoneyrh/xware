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

#include "xconsole.h"
#include "xstring_algorithm.h"
#include <conio.h>

#ifdef UNICODE
#define _gettch		_getwch
#define _puttch		_putwch
#define istprint    iswprint
#else
#define _gettch		_getch
#define _puttch		_putch
#define istprint    isprint
#endif

#define ISTAB(c)      ((c) == _X('\t'))
#define ISENTER(c)    ((c) == _X('\r') || (c) == _X('\n'))
#define ISESC(c)      ((c) == _X(''))
#define ISBREAK(c)    ((c) == _X('\003'))
#define ISBKSPC(c)    ((c) == _X('\b'))

namespace xws
{

static void backspace(size_t distance)
{
    for (size_t i = 0; i < distance; ++ i)
    {
        _puttch(_X('\10'));
    }
    for (size_t i = 0; i < distance; ++ i)
    {
        _puttch(_X(' '));
    }
    for (size_t i = 0; i < distance; ++ i)
    {
        _puttch(_X('\10'));
    }
    fflush(stdout);
}

xconsole::xconsole()
{
}

xconsole::~xconsole()
{
}

xstring xconsole::input(const xstring& prompt)
{
    xstring input;
    xcout << prompt;
    while (true)
    {
        xchar c = _gettch();
        // Enter
        if (ISENTER(c))
        {
            break;
        }
        // CTRL + C
        if (ISBREAK(c))
        {
            // Keyboard interrupt
            throw std::exception("Keyboard Interrupt");
        }
        // Backspace
        if (ISBKSPC(c))
        {
            if (!input.empty())
            {
                input = input.substr(0, input.length() - 1);
                // Go back one char
                _puttch(_X('\10'));
                // Erase this character
                _puttch(_X(' '));
                // Go back for waiting next char
                _puttch(_X('\10'));
                fflush(stdout);
            }
        }
        else// if (istprint(c))
        {
            input.append(1, c);
            // Echo this character
            _puttch(c);
            fflush(stdout);
        }
    }
    xcout << std::endl;
    return input;
}

xstring xconsole::input_password(const xstring& prompt)
{
    xstring input;
    xcout << prompt;
    while (true)
    {
        xchar c = _gettch();
        // Enter
        if (ISENTER(c))
        {
            break;
        }
        // CTRL + C
        if (ISBREAK(c))
        {
            // Keyboard interrupt
            throw std::exception("Keyboard Interrupt");
        }
        // Backspace
        if (ISBKSPC(c))
        {
            if (!input.empty())
            {
                input = input.substr(0, input.length() - 1);
                // Go back one char
                _puttch(_X('\10'));
                // Erase this character
                _puttch(_X(' '));
                // Go back for waiting next char
                _puttch(_X('\10'));
                fflush(stdout);
            }
        }
        else// if (istprint(c))
        {
            input.append(1, c);
            // Echo this character
            _puttch(_X('*'));
            fflush(stdout);
        }
    }
    xcout << std::endl;
    return input;
}

xhint_console::xhint_console(const xstring_list& hints) : hints_(hints)
{
}

xhint_console::~xhint_console()
{
}

xstring xhint_console::input(const xstring& prompt)
{
    xstring input;
    xcout << prompt;
    while (true)
    {
        xchar c = _gettch();
handle_next_char:
        // Enter
        if (ISENTER(c))
        {
            break;
        }
        // CTRL + C
        if (ISBREAK(c))
        {
            // Keyboard interrupt
            throw std::exception("Keyboard Interrupt");
        }
        // Backspace
        if (ISBKSPC(c))
        {
            if (!input.empty())
            {
                input = input.substr(0, input.length() - 1);
                // Go back one char
                _puttch(_X('\10'));
                // Erase this character
                _puttch(_X(' '));
                // Go back for waiting next char
                _puttch(_X('\10'));
                fflush(stdout);
            }
        }
        // Tab
        else if (ISTAB(c))
        {
            if (input.length())
            {
                for (xstring_list::iterator iter = hints_.begin(), end = hints_.end();
                        iter != end; ++ iter)
                {
                    if (iter->length() >= input.length())
                    {
                        xstring candidate = iter->substr(0, input.length());
                        if (boost::iequals(input, candidate))
                        {
                            // Find the candidate, output to the console
                            for (size_t i = input.length(); i < iter->length(); ++ i)
                            {
                                _puttch((*iter)[i]);
                            }
                            fflush(stdout);
                            c = _gettch();
                            if (ISTAB(c))
                            {
                                backspace(iter->length() - input.length());
                            }
                            else
                            {
                                input = *iter;
                                goto handle_next_char;
                            }
                        }
                    }
                }
            }
        }
        else// if (istprint(c))
        {
            input.append(1, c);
            // Echo this character
            _puttch(c);
            fflush(stdout);
        }
    }
    xcout << std::endl;
    return input;
}

} // namespace xws

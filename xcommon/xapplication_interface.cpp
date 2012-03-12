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

#include "xapplication_interface.h"
#include "xformat.h"

namespace xws
{

xapplication_interface::xapplication_interface(int argc, xchar* argv[])
{
}

xapplication_interface::xapplication_interface(int argc, xchar* argv[], const xprogram_options::options_description& options_description)
{
    xprogram_options::store(
            xprogram_options::parse_command_line(argc, argv, options_description),
                                                    options_vars_);
}

xapplication_interface::~xapplication_interface()
{
}

bool xapplication_interface::has_option(const astring& name) const
{
    return options_vars_.count(name) > 0;
}

xstring xapplication_interface::version_str() const
{
    xformat format(xformat(_X("%1% version %2%")) % name() % version().x_str());
    return format.str();
}

xstring xapplication_interface::legal_statement() const
{
    return _X("Copyright (C) xWorkshop.\n")
           _X("You could use and distribute this utility freely without any limitation.");
}

xstring xapplication_interface::bug_statement() const
{
    return _X("Report bug to stoneyrh@gmail.com.");
}

} // namespace xws

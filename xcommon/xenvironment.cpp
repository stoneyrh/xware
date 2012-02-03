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

#include "xenvironment.h"
#include <cstdlib>
#include <boost/scoped_array.hpp>
#ifdef WINDOWS
#include <windows.h>
#endif

namespace xws
{

xenvironment::xenvironment()
{
}

xenvironment::~xenvironment()
{
}

xstring xenvironment::operator [](const xstring &key)
{
    return get(key);
}

xstring xenvironment::get(const xstring &key)
{
    xstring value;
    variables::iterator pos = variables_.find(key);
    if (pos == variables_.end())
    {
        value = get_from_system(key);
        variables_.insert(variables::value_type(key, value));
    }
    else
    {
        value = pos->second;
    }
    return value;
}

bool xenvironment::has(const xstring &key)
{
    variables::iterator pos = variables_.find(key);
    if (pos == variables_.end())
    {
        try
        {
            xstring value = get_from_system(key);
            variables_.insert(variables::value_type(key, value));
        }
        catch (xvariable_not_exist&)
        {
            return false;
        }
    }
    return true;
}

xstring xenvironment::get_from_system(const xstring &key)
{
    xstring value;
#ifdef WINDOWS
    xchar buffer[MAX_PATH] = _X("\0");
    if (GetEnvironmentVariable(key.c_str(), buffer, MAX_PATH))
    {
        value.assign(buffer);
    }
    else
    {
        if (GetLastError() == ERROR_ENVVAR_NOT_FOUND)
        {
            // No this environment variable
            throw xvariable_not_exist();
        }
    }
#else
    std::string name = match_str<std::string, xstring>::apply(key);
    char *cvalue = getenv(name.c_str());
    if (cvalue)
    {
        value = match_str<xstring, std::string>::apply(cvalue);
    }
    else
    {
        // No this environment variable
        throw xvariable_not_exist();
    }
#endif // WINDOWS
    return value;
}

} // namespace xws

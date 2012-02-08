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

#ifndef _XUUID_H_
#define _XUUID_H_

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <set>

namespace xws
{
namespace xuuids = boost::uuids;
typedef xuuids::nil_generator       xuuid_nil_generator;
typedef xuuids::name_generator      xuuid_name_generator;
typedef xuuids::string_generator    xuuid_string_generator;
typedef xuuids::random_generator    xuuid_random_generator;
typedef xuuids::uuid                xuuid;
typedef std::set<xuuid>             xuuid_set;

#define xuuid_to_string             xuuids::to_string
#define xuuid_to_wstring            xuuids::to_wstring

#ifdef UNICODE
#define xuuid_to_xstring            xuuid_to_wstring
#else
#define xuuid_to_xstring            xuuid_to_string
#endif

} // namespace xws

#endif

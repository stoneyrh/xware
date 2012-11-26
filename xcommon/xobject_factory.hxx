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

#ifndef _XOBJECT_FACTORY_H_
#define _XOBJECT_FACTORY_H_

#include <map>
#include "xlogger.hxx"
#include "xlocale.hxx"

namespace xws
{

template <class T, class K = int, class C = T* (*)()>
class xobject_factory
{
    public:
        typedef K Key;
        typedef C Creator;
        typedef std::map<Key, Creator> Creators;
        //
        xobject_factory() {}
        ~xobject_factory() {}
        //
        bool register_creator(const Key& key, const Creator creator)
        {
            if (creators_.find(key) == creators_.end())
            {
                creators_[key] = creator;
                return true;
            }
            xdebug_info(xchar_format(xtr(_X("Creator with key = {1} has a duplicate value."))) % key);
            return false;
        }
        bool unregister_creator(const Key& key)
        {
            typename Creators::iterator pos = creators_.find(key);
            if (pos != creators_.end())
            {
                creators_.erase(pos);
                return true;
            }
            return false;
        }
        Creator creator_of(const Key& key) const
        {
            typename Creators::const_iterator pos = creators_.find(key);
            if (pos != creators_.end())
            {
                return pos->second;
            }
            return 0;
        }
        bool has_creator(const Key& key) const
        {
            typename Creators::const_iterator pos = creators_.find(key);
            return pos != creators_.end();
        }
    private:
        Creators creators_;
};

} // namespace xws

#endif

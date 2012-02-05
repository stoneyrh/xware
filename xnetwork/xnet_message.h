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

#ifndef _X_NET_MESSAGE_H_
#define _X_NET_MESSAGE_H_

#include "xglobal.h"
#include "xbyte_array.h"
#include "xdata_stream.h"
#include "xversionable.h"
#include "xarchive.h"
#include "xsmart_ptr.h"
#include <vector>
#include <map>

#define DECLARE_XNET_MESSAGE(klass)                      \
private:                                                 \
    static xnet_message* create##klass()                 \
    {                                                    \
        return new klass();                              \
    }                                                    \
    class klass##_register                               \
    {                                                    \
        public:                                          \
            klass##_register()                           \
            {                                            \
                klass::register_creator(_X(#klass),      \
                        &klass::create##klass);          \
            }                                            \
    };                                                   \
private:                                                 \
    static klass##_register register_;                   \

//
#define IMPLEMENT_XNET_MESSAGE(klass)                    \
    klass::klass##_register klass::register_;

namespace xws
{

class xnet_message;
typedef xnet_message* (*xnet_message_creator_t)();

typedef xshared_ptr<xnet_message>::type xnet_message_ptr;
typedef std::vector<xnet_message_ptr>   xnet_message_set;
typedef std::map<xmid_t, xnet_message_creator_t> id_to_creator_t;

class xnet_message_ids;

class xnet_message : public xversionable
{
    public:
        explicit xnet_message(xversion_t version = 1);
        virtual ~xnet_message();

        xmid_t id() const { return id_; }
        void set_id(xmid_t id) { id_ = id; }

        bool to_byte_array(xbyte_array& byte_array);
        static xnet_message_set from_byte_array(const xbyte_array& byte_array, xsize_t* consumed_size = 0);

        static xnet_message_ptr create_message(xmid_t id);
        static xnet_message_ptr create_message(const xstring& name);
        static xnet_message_ids& net_message_ids();
    protected:
        virtual bool to_data_stream(xdata_stream& stream) = 0;
        virtual bool from_data_stream(xdata_stream& stream) = 0;

        static void register_creator(const xstring& klass, xnet_message_creator_t creator);
        static id_to_creator_t& id_to_creator();

    private:
        xmid_t id_;
};

} // namespace xws

#endif

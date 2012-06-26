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

#include "xnet_message.h"
#include "xnet_message_ids.h"
#include "xassert.h"
#include "xnetwork.h"
#include "xlogger.h"
#include "xlocale.h"

namespace xws
{

xnet_message_ids& xnet_message::net_message_ids()
{
    static xnet_message_ids mids;
    return mids;
}

xnet_message_ptr xnet_message::create_message(xmid_t id)
{
    id_to_creator_t& id_2_creator = id_to_creator();
    xnet_message_creator_t creator = id_2_creator[id];
    if (creator)
    {
        xnet_message_ptr message((*creator)());
        if (message)
        {
            message->set_id(id);
            return message;
        }
    }
    //
    static xnet_message_ptr none;
    return none;
}

xnet_message_ptr xnet_message::create_message(const xstring& name)
{
    const xnet_message_ids& mids = net_message_ids();
    return create_message(mids.id_of(name));
}

xnet_message::xnet_message(xversion_t version) : xversionable(version)
{
}

xnet_message::~xnet_message()
{
}

bool xnet_message::to_byte_array(xbyte_array& byte_array)
{
    xdata_stream stream(&byte_array);
    // Move to the end just in case of byte_array is not empty
    stream.seek(0, seek_end);
    // This is the old size, will be overwritten later
    std::size_t size = byte_array.size();
    stream << size << id() << version();
    if (this->to_data_stream(stream))
    {
        // Move back to the postition where size should be located
        stream.seek(size, seek_beg);
        // Delta size should be written
        size = byte_array.size() - size;
        // Overwrite the size field
        stream << size;
        return true;
    }
    return false;
}

xnet_message_set xnet_message::from_byte_array(const xbyte_array& byte_array, xsize_t* consumed_size)
{
    xnet_message_set set;
    xdata_stream stream(byte_array);
    xsize_t recognized_size = 0;
    while (!stream.at_end())
    {
        xsize_t size = 0;
        xsize_t begin_pos = stream.pos();
        stream >> size;
        xdebug_info(xchar_format(xtr(_X("byte_array.size() = {1}, size read from stream = {2}."))) % byte_array.size() % size);
        if (size == 0 || size > byte_array.size())
        {
            xdebug_info(_X("The size indicates in the stream is not correct."));
        }
        else
        {
            xmid_t id = 0;
            xversion_t version = 0;
            stream >> id >> version;
            xnet_message_ptr message = create_message(id);
            if (message)
            {
                message->set_version(version);
                if (message->from_data_stream(stream))
                {
                    xsize_t end_pos = stream.pos();
                    xsize_t stream_offset = end_pos - begin_pos;
                    // Stream goes exactly the same steps as that of a message size
                    // Otherwise it is not a correct message
                    if (stream_offset == size)
                    {
                        set.push_back(xnet_message_ptr(message));
                        recognized_size += size;
                    }
                    else
                    {
                        xdebug_info(xchar_format(xtr(_X("The size of message (= {1}) does not match that read out from stream (= {2})."))) % size % stream_offset);
                    }
                }
            }
            else
            {
                xdebug_info(xchar_format(xtr(_X("Failed to create a message with id = {1}."))) % id);
            }
        }
    }
    if (consumed_size)
    {
        *consumed_size = recognized_size;
    }
    return set;
}

void xnet_message::register_creator(const xstring& klass, xnet_message_creator_t creator)
{
    xdebug_info(xchar_format(xtr(_X("Registering creator for message \"{1}\"..."))) % klass);
    xnet_message_ids& mids = net_message_ids();
    xmid_t id = mids.id_of(klass);
    xassert(id != INVALID_XMID);
    id_to_creator_t& id_2_creator = id_to_creator();
    id_2_creator.insert(id_to_creator_t::value_type(id, creator));
}

id_to_creator_t& xnet_message::id_to_creator()
{
    static id_to_creator_t id_2_creator;
    return id_2_creator;
}

} // namespace xws

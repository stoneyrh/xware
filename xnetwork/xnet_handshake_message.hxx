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

#ifndef _XNET_HANDSHAKE_MESSAGE_H_
#define _XNET_HANDSHAKE_MESSAGE_H_

#include "xnet_message.hxx"
#include "xuuid.hxx"

namespace xws
{

class xnet_handshake_message : public xnet_message
{
    public:
        xnet_handshake_message();
        virtual ~xnet_handshake_message();

        const xuuid& uuid() const { return uuid_; }
        xsize_t heartbeat_interval() const { return heartbeat_interval_; }
        xsize_t heartbeat_threshold() const { return heartbeat_threshold_; }
        // Create UUID from a string
        void set_uuid(const xstring& uuid);
        void set_heartbeat_interval(xsize_t heartbeat_interval) { heartbeat_interval_ = heartbeat_interval; }
        void set_heartbeat_threshold(xsize_t heartbeat_threshold) { heartbeat_threshold_ = heartbeat_threshold; }
    protected:
        virtual bool to_data_stream(xdata_stream& stream)
        {
            stream << heartbeat_interval_ << heartbeat_threshold_;
            stream.write(&uuid_, sizeof(uuid_));
            return stream.good();
        }
        virtual bool from_data_stream(xdata_stream& stream)
        {
            switch (version())
            {
                case 1:
                    stream >> heartbeat_interval_ >> heartbeat_threshold_;
                    stream.read(&uuid_, sizeof(uuid_));
                    break;
                default:
                    break;
            }
            return stream.good();
        }
    private:
        // Specifying how frequent the heartbeat will occur
        // A positive value is a valid number of seconds
        // 0 means heartbeat disabled
        xsize_t heartbeat_interval_;
        // Specifying how long it could bear if there is no heartbeat
        // This value must be satisfied heartbeat_threshold_ >= heartbeat_interval_
        // If heartbeat_interval_ is 0, this value is meaningless
        xsize_t heartbeat_threshold_;
        // Each application should contains a UUID for unique identifying this application
        // The client could only communicates with approvate server with the same UUID
        xuuid uuid_;
        DECLARE_XNET_MESSAGE(xnet_handshake_message)
};

typedef xshared_ptr<xnet_handshake_message>::type xnet_handshake_message_ptr;

} // namespace xws

#endif

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

#ifndef _X_NET_IO_OBJECT_H_
#define _X_NET_IO_OBJECT_H_

#include "xglobal.h"
#include "xnetwork.h"
#include "xsmart_ptr.h"
#include "xbyte_array.h"
#include "xsignal.h"
#include "xerror_code.h"

#define READ_BUFFER_SIZE (8 * 1024)

namespace xws
{
class xnet_io_object : public xenable_shared_from_this<xnet_io_object>
{
    public:
        typedef xshared_ptr<xnet_io_object>::type ptr_t;
        typedef xsignal<void (const xbyte_array&)> data_read_sig_t;
        typedef xsignal<void ()> data_write_sig_t;
        typedef xsignal<void (const xerror_code&)> error_sig_t;
        xnet_io_object();
        virtual ~xnet_io_object();
        virtual void write(const xbyte_array_ptr& byte_array) = 0;
        virtual void read(xbyte_array& byte_array) = 0;
        virtual void start_async_read() = 0;
        virtual void do_async_write(const xbyte_array& byte_array) = 0;
        virtual void shutdown() = 0;
        virtual void cancel() = 0;
        virtual void close() = 0;
        virtual xio_service& io_service() = 0;

        data_read_sig_t& data_read_sig() { return data_read_sig_; }
        data_write_sig_t& data_write_sig() { return data_write_sig_; }
        error_sig_t& data_read_error_sig() { return data_read_error_sig_; }
        error_sig_t& data_write_error_sig() { return data_write_error_sig_; }

    protected:
        xbyte_ptr read_buffer() { return read_buffer_; }

    protected:
        virtual void on_data_read(xbyte_ptr data, const xerror_code& error_code, xsize_t bytes_transfered) = 0;
        virtual void on_data_write(const xbyte_array_ptr& byte_array, const xerror_code& error_code, xsize_t bytes_transfered) = 0;
    private:
        xbyte_ptr read_buffer_;
        data_read_sig_t data_read_sig_;
        data_write_sig_t data_write_sig_;
        error_sig_t data_read_error_sig_;
        error_sig_t data_write_error_sig_;
};

typedef xnet_io_object::ptr_t xnet_io_object_ptr;

}

#endif

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

#include "xnet_service.h"
#include "xbind.h"
#include "xlogger.h"

namespace xws
{

xnet_service::xnet_service(const xnet_io_object_ptr& io_object) : io_object_(io_object)
{
    xdebug_info(_X("Creating xnet_service..."));
}

xnet_service::~xnet_service()
{
    xdebug_info(_X("Deleting xnet_service..."));
}

void xnet_service::run()
{
    xdebug_info(_X("xnet_service started."));
    net_service_started_sig_(shared_from_this());
    do
    {
        try
        {
            io_object_->data_read_sig().connect(xbind(&xnet_service::on_data_read, this, _1, _2));
            io_object_->error_sig().connect(xbind(&xnet_service::on_error, this, _1));
            io_object_->start_async_read();
            // It could be stopped before running any command
            xthis_thread::interruption_point();
            //
            do
            {
                net_command command = net_commands_.get();
                // Check interruption before and after running a command
                xthis_thread::interruption_point();
                command();
                xthis_thread::interruption_point();
            } while(true);
        }
        catch (xthread_interrupted&)
        {
            break;
        }
        catch (...)
        {
        }
    } while (true);
    net_service_stopped_sig_(shared_from_this());
    xdebug_info(_X("xnet_service stopped."));
}

void xnet_service::start()
{
    xdebug_info(_X("Starting xnet_service..."));
    xthread service_runner(xbind(&xnet_service::run, shared_from_this()));
}

void xnet_service::stop()
{
    xdebug_info(_X("Stopping xnet_service..."));
    net_commands_.put(xbind(&xnet_service::raise_stop_interruption, shared_from_this()));
}

void xnet_service::raise_stop_interruption()
{
    // This function must not be called directly
    throw xthread_interrupted();
}

void xnet_service::on_data_read(xnet_io_object_ptr& io_object, const xbyte_array& byte_array)
{
    std::cout << std::string((char*)byte_array.data(), (char*)byte_array.data() + byte_array.size()) << std::endl;
}

void xnet_service::on_error(const xerror_code& error_code)
{
    xdebug_info(xformat(_X("xnet_service encounters error with category = %1%, code = %2%.")) % error_code.category().name() % error_code.value());
    // misc_errors
    if (error_code.category() == xmisc_category)
    {
        switch (error_code.value())
        {
            case xasio_error::eof:
                stop();
                break;
            default:
                break;
        }
    }
}

} // namespace xws

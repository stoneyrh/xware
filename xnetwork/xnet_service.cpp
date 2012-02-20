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
#include "xassert.h"
#include "xnet_message.h"
#include "xposix_time.h"
#include "xfinal_command.h"

namespace xws
{

xnet_service::xnet_service(const xnet_io_object_ptr& io_object) : xnet_terminal(io_object)
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
    net_service_started_sig_(xdynamic_pointer_cast<xnet_service>(shared_from_this()));
    // A scope block
    {
        init_asynchrous_operation();
        xfinal_command deinit_asynchrous_operation(xbind(&xnet_service::deinit_asynchrous_operation, this));
        io_object_->start_async_read();
        do
        {
            try
            {
                // It could be stopped before running any command
                xthis_thread::interruption_point();
                // Once connected, we start monitoring hand shake message
                // If there is no hand shake message for some period of time, then the service will exit
                start_monitor_handshake();
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
                // TODO: Check what exception here, if not a serious one, just go on
                // A series exception will result in service termination
            }
        } while (true);
        // Remove all commands in the queue
        net_commands_.clear();
    }
    try
    {
        xdebug_info(_X("Terminating the IO object..."));
        // Use final command to make sure io_object is terminated properly
        // This is because io_object_->cancel might throw exception, in that case, shutdown and close won't be run
        xfinal_command close_io_object(xbind(&xnet_io_object::close, io_object_));
        xfinal_command shutdown_io_object(xbind(&xnet_io_object::shutdown, io_object_));
        // Cancel IO may throw exception, and it may not work on Windows less than XP
        // Please consult boost documentation for more information
        xfinal_command cancel_io_object(xbind(&xnet_io_object::cancel, io_object_));
    }
    catch (...)
    {
    }
    // Notify service stopped
    net_service_stopped_sig_(xdynamic_pointer_cast<xnet_service>(shared_from_this()));
    xdebug_info(_X("xnet_service stopped."));
}

void xnet_service::start()
{
    xdebug_info(_X("Starting xnet_service..."));
    xthread service_runner(xbind(&xnet_service::run, xdynamic_pointer_cast<xnet_service>(shared_from_this())));
}

void xnet_service::stop()
{
    xdebug_info(_X("Stopping xnet_service..."));
    net_commands_.put(xbind(&xnet_service::raise_stop_interruption, xdynamic_pointer_cast<xnet_service>(shared_from_this())));
}

void xnet_service::raise_stop_interruption()
{
    // This function must not be called directly
    throw xthread_interrupted();
}

void xnet_service::on_data_read(const xbyte_array& byte_array)
{
    // We handle the data in service thread for not blocking the read thread
    net_commands_.put(xbind(&xnet_service::handle_byte_array, xdynamic_pointer_cast<xnet_service>(shared_from_this()), byte_array));
}

void xnet_service::on_data_read_error(const xerror_code& error_code)
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

void xnet_service::on_handshake_timeout(const xerror_code& error_code)
{
    // If the operatio is aborted, then no need to stop
    if (error_code != xasio_error::operation_aborted)
    {
        // At this point, it fails to handshake with peer side, so stop the service
        xdebug_info(_X("Failed to handshake with peer side, the service will terminate."));
        stop();
    }
}

void xnet_service::on_heartbeat_timeout(const xerror_code& error_code)
{
}

} // namespace xws

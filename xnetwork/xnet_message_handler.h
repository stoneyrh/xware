#ifndef _XNET_MESSAGE_HANDLER_H_
#define _XNET_MESSAGE_HANDLER_H_

#include "xnet_message.h"
#include "xsmart_ptr.h"

namespace xws
{


class xnet_message_handler_context
{
    public:
        xnet_message_handler_context() {}
        virtual ~xnet_message_handler_context() {}
};

class xnet_message_handler
{
    public:
        xnet_message_handler() {}
        virtual ~xnet_message_handler() {}

        virtual void handle_message(xnet_message_ptr message, xnet_message_handler_context_ptr context) = 0;
};

typedef xshared_ptr<xnet_message_handler>::type xnet_message_handler_ptr;

} // namespace xws

#endif

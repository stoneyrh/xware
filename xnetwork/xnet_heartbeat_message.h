#ifndef _XNET_HEARTBEAT_MESSAGE_H_
#define _XNET_HEARTBEAT_MESSAGE_H_

#include "xnet_message.h"

namespace xws
{

class xnet_heartbeat_message : public xnet_message
{
    public:
        xnet_heartbeat_message();
        virtual ~xnet_heartbeat_message();
    protected:
        virtual bool to_data_stream(xdata_stream& stream)
        {
            return stream.good();
        }
        virtual bool from_data_stream(xdata_stream& stream)
        {
            return stream.good();
        }
        DECLARE_XNET_MESSAGE(xnet_heartbeat_message)
};

} // namespace xws

#endif

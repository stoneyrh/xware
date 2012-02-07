#ifndef _XNET_HANDSHAKE_MESSAGE_H_
#define _XNET_HANDSHAKE_MESSAGE_H_

#include "xnet_message.h"

namespace xws
{

class xnet_handshake_message : public xnet_message
{
    public:
        xnet_handshake_message();
        virtual ~xnet_handshake_message();
    protected:
        virtual bool to_data_stream(xdata_stream& stream)
        {
            return stream.good();
        }
        virtual bool from_data_stream(xdata_stream& stream)
        {
            return stream.good();
        }
        DECLARE_XNET_MESSAGE(xnet_handshake_message)
};

} // namespace xws

#endif

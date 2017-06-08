/// \file protocol.hpp Protocol utilites

#ifndef MUTE_PROTOCOL_HPP
#define MUTE_PROTOCOL_HPP

namespace mute {

enum class MessageType: int {
    // Basic protocol
    Hello,
    Ping,
    Pong,

    // Node management
    Sync,
    Create,
    Destroy,
    Move,
};


}

#endif // MUTE_PROTOCOL_HPP

#pragma once

#include <linux/can.h>

//#include <cstddef>
#include <cstdint>
#include <vector>

#include "exceptions/CanException.hpp"


namespace libsocketcanpp
{
    class CanMessage
    {
        public:
        CanMessage(can_frame frame) :
          frame(frame)
        {   
        }

        const canid_t GetId() const { return frame.can_id; }
        std::vector<std::uint8_t> GetPayload() const { return std::vector<std::uint8_t>(frame.data,frame.data + frame.len8_dlc); }
        size_t GetPayloadSize() const { return frame.len8_dlc; }

        can_frame GetRawCanFrame() const { return frame; }

        private:
        struct can_frame frame;
        
    };
} //namespace libsocketcanpp
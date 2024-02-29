#pragma once

#include <linux/can.h>

#include <chrono>
#include <cstdint>
#include <vector>


namespace libsocketcanpp
{
    class CanMessage
    {
        public:
        CanMessage(const can_frame& frame,const std::chrono::time_point<std::chrono::system_clock>& timestamp) :
            frame(frame),
            timestamp(timestamp)
        {
        }
        virtual ~CanMessage() = default;

        const canid_t GetId() const { return frame.can_id; }
        const std::chrono::time_point<std::chrono::system_clock> GetTimestamp() const { return timestamp; }
        std::vector<std::uint8_t> GetPayload() const { return std::vector<std::uint8_t>(frame.data,frame.data + frame.len8_dlc); }
        size_t GetPayloadSize() const { return frame.len8_dlc; }

        can_frame GetRawCanFrame() const { return frame; }

        private:
        struct can_frame frame;
        std::chrono::time_point<std::chrono::system_clock> timestamp;
        
    };
} //namespace libsocketcanpp

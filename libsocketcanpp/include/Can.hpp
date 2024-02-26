#pragma once

#include <chrono>
#include <optional>
#include <string>
#include <vector>

#include "CanMessage.hpp"


namespace libsocketcanpp
{
    
    class Can
    {
        public:
        Can(const std::string& canInterface);
        ~Can();

        //bool WaitForMessages(std::chrono::milliseconds timeout);
        std::vector<CanMessage> WaitForMessages(std::chrono::milliseconds timeout);
        bool sendMessage(const CanMessage& message);
        

        private:
        void SocketInit();
        std::optional<CanMessage> ReadMessage();

        int32_t fd;

        const std::string canInterface;
    };

} //namespace libsocketcan

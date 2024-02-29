#pragma once

#include <chrono>
#include <functional>
#include <map>
#include <memory>
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
        std::vector<std::shared_ptr<CanMessage>> WaitForMessages(std::chrono::milliseconds timeout);
        bool SendMessage(std::shared_ptr<CanMessage> msg);

        template <typename MSG_T>
        void RegisterCreator(canid_t id) { creators[id] = [&](const can_frame& frame,const std::chrono::time_point<std::chrono::system_clock>& timestamp) { return std::make_shared<MSG_T>(frame,timestamp); }; }

        private:
        void SocketInit();
        std::shared_ptr<CanMessage> ReadMessage();

        int32_t fd;

        const std::string canInterface;

        std::map<canid_t,std::function<std::shared_ptr<CanMessage>(const can_frame&, const std::chrono::time_point<std::chrono::system_clock>&)>> creators;
    };

} //namespace libsocketcan

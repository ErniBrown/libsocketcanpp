#include "Can.hpp"

#include <iostream>
#include <thread>


using namespace libsocketcanpp;

int main(int argc, char* argv[])
{
    Can can("can1");

    while(1)
    {
        auto now = std::chrono::steady_clock::now();
        auto messages = can.WaitForMessages(std::chrono::milliseconds(20));

        std::cout << "Messages count = " << messages.size() << std::endl;

        std::this_thread::sleep_until(now + std::chrono::milliseconds(100));
    }
    
    return 0;
}
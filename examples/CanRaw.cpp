#include "Can.hpp"

#include <iostream>


using namespace libsocketcanpp;

int main(int argc, char* argv[])
{
    Can can("can1");

    auto gianni = can.WaitForMessages(std::chrono::milliseconds(20));

    std::cout << "Messages count = " << gianni.size() << std::endl;
    
    return 0;
}
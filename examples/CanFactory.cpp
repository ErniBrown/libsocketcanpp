#include "Can.hpp"

#include <iostream>


using namespace libsocketcanpp;

class SystemState : public libsocketcanpp::CanMessage
{
    public:
    SystemState(const can_frame& frame,const std::chrono::time_point<std::chrono::system_clock>& timestamp) : libsocketcanpp::CanMessage(frame, timestamp)
    {
        faultNumber = frame.data[0] | frame.data[1] << 8;
        warningNumber = frame.data[2];
        //state = static_cast<CUSTOMER_STATE>(frame.data[4]);
        fansRunning = frame.data[6] & 0x80;
        copyBitOut = frame.data[7] & 0x80;
        alignment = frame.data[7] & 0x7F;
    }

    void PrintSystemState()
    {
        std::cout << "faultNumber: " << faultNumber << std::endl;
        std::cout << "warningNumber: " << warningNumber << std::endl;
        //std::cout << "state: " << state << std::endl;
        std::cout << "fansRunning: " << fansRunning << std::endl;
        std::cout << "copyBitOut: " << copyBitOut << std::endl;
        std::cout << "alignment: " << alignment << std::endl;
    }

    static const canid_t ID = 0x1D0;

    private:
    //CUSTOMER_STATE state = CUSTOMER_STATE::CUSTOMER_WAITING;

    uint16_t faultNumber;
    uint8_t warningNumber;
    

    bool        fansRunning;
    bool        copyBitOut;
    uint8_t     alignment;
};


int main(int argc, char* argv[])
{
    Can can("can1");
    can.RegisterCreator<SystemState>(SystemState::ID);

    auto messages = can.WaitForMessages(std::chrono::milliseconds(20));

    std::cout << "Messages count = " << messages.size() << std::endl;
    
    return 0;
}
#include "Can.hpp"

#include "exceptions/CanException.hpp"

#include <fcntl.h>
#include <linux/can.h>
//#include <linux/can/raw.h>
#include <net/if.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <sys/socket.h>
//#include <sys/types.h>
#include <unistd.h>

#include <iostream>


using namespace libsocketcanpp;

Can::Can(const std::string& canInterface) : 
    canInterface(canInterface)
{
    SocketInit();
}


Can::~Can()
{
    //if (fd <= 0) { throw SocketCanCloseException(); }
    //if (close(fd) == -1) { throw SocketCanCloseException(); }
}


std::vector<CanMessage> Can::WaitForMessages(std::chrono::milliseconds timeout)
{
    std::vector<CanMessage> retVal;

    if (fd < 0)
    {
        std::cout << "TO BE CHANGED: INVALID SOCKET: " << __FILE__ << " at line " << __LINE__ << std::endl;
        //throw InvalidSocketException("Invalid socket!", fd); }
    }

    fd_set readFileDescriptors;
    timeval waitTime;
    waitTime.tv_sec = timeout.count() / 1000;
    waitTime.tv_usec = timeout.count() * 1000;

    FD_ZERO(&readFileDescriptors);
    FD_SET(fd, &readFileDescriptors);
    int ret = select(fd + 1, &readFileDescriptors, 0, 0, &waitTime);

    //return ret > 0;
    if(ret > 0)
    {
        while(true)
        {
            auto aMessage = ReadMessage();
            if(!aMessage.has_value())
                break;

            retVal.push_back(aMessage.value());
        }
    }

    return retVal;
}


bool Can::sendMessage(const CanMessage& message)
{
    if(fd < 0)
    {
        throw SocketCanFileDescriptorException();
    }

    //unique_lock<mutex> locky(_lockSend);

    int32_t bytesWritten = 0;

    can_frame frame = message.GetRawCanFrame();
    bytesWritten = write(fd, (const void*)&frame, sizeof(frame));

    if (bytesWritten == -1)
        throw SocketCanWriteError();

    return bytesWritten > 0;
}


std::optional<CanMessage> Can::ReadMessage()
{
    if (fd < 0)
        throw SocketCanFileDescriptorException();

    int32_t readBytes{0};
    can_frame canFrame;
    memset(&canFrame, 0, sizeof(can_frame));
    
    readBytes = read(fd, &canFrame, sizeof(can_frame));
    /*if (readbytes < 0)
        throw AnExceptions with these info: errno, strerror(errno)*/
    
    std::cout << "Bytes: " << readBytes << std::endl;

    if (readBytes > 0)
        return CanMessage(canFrame);
    
    return std::nullopt;
    //return CanMessage{canFrame};
}


void Can::SocketInit()
{
    struct sockaddr_can address;
    struct ifreq ifaceRequest;
    int64_t fdOptions = 0;
    int ret = -1;

    memset(&address, 0, sizeof(sizeof(struct sockaddr_can)));
    memset(&ifaceRequest, 0, sizeof(sizeof(struct ifreq)));

    fd = socket(PF_CAN, SOCK_RAW, CAN_RAW);

    if (fd == -1) 
        throw SocketCanInitException(errno);

    strcpy(ifaceRequest.ifr_name, canInterface.c_str());

    if ((ret = ioctl(fd, SIOCGIFINDEX, &ifaceRequest)) == -1)
    {
        throw SocketCanInitException(errno);
    }

    fdOptions = fcntl(fd, F_GETFL);
    fdOptions |= O_NONBLOCK;
    ret = fcntl(fd, F_SETFL, fdOptions);

    address.can_family = AF_CAN;
    address.can_ifindex = ifaceRequest.ifr_ifindex;

    /*setCanFilterMask(_canFilterMask);*/

    ret = bind(fd, (struct sockaddr*)&address, sizeof(address));
    if (ret == -1) {
        throw SocketCanInitException(errno);
    }
}

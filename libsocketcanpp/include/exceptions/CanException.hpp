#pragma once

#include <cstring>
#include <format>
#include <stdexcept>

namespace libsocketcanpp
{
    
    class SocketCanInitException : public std::runtime_error
    {
        public:
        SocketCanInitException(error_t error) : runtime_error(std::string("Socket init error: ").append(std::strerror(error))) {}
    };

    class SocketCanFileDescriptorException : public std::runtime_error
    {
        public:
        SocketCanFileDescriptorException() : runtime_error("Invalid socket!") {}
    };

    class SocketCanCloseException : public std::runtime_error
    {
        public:
        SocketCanCloseException() : runtime_error("Error closing socket") {}
    };

    class SocketCanWriteError : public std::runtime_error
    {
        public:
        SocketCanWriteError() : runtime_error("Error writing message") {}
    };

}

#ifndef _HEADER_SERVER_EXCEPTION
#define _HEADER_SERVER_EXCEPTION
#include <Arduino.h>
#include <exception>
#include "ServerException.hpp"

class ServerException : public std::exception
{
    public:
        ServerException(const char* msg, uint8_t code)
            : _msg(msg), _code(code)
        {
        }

        uint8_t code() { return _code; }
        const char* what() { return _msg; }
    private:
        const char* _msg;
        uint8_t _code;
};

#endif // _HEADER_SERVER_EXCEPTION
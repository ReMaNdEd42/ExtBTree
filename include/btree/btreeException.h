#ifndef __BSE_EXCEPTION_H__
#define __BSE_EXCEPTION_H__
#include <exception>
#include <iostream>
class BtreeException : public std::exception
{
private:
    const char *msg;
public:
    BtreeException(const char *msg) : std::exception(), msg(msg) {}

    const char *what() const throw()
    {   
        std::cout << msg;
        return msg;
    }
};
#endif
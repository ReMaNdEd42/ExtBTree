#ifndef __ALLOCATOR_H__
#define __ALLOCATOR_H__
#include <cstddef>
/*
    You can write your own allocator implemntation.
    I gues you can find better practice for it :3
    good luck bro!
*/

class Allocator
{
private:
public:
    Allocator(){};
    virtual ~Allocator(){};

    virtual std::byte *allocate() = 0;
    virtual void dellocate(std::byte *addr) = 0;
    virtual void free() = 0;

    virtual std::byte *getStart() = 0;
};

#endif // __ALLOCATOR_H__

#include "allocator.h"
#include <cstdio>
#include <iostream>
#include <string>
#include <cstdint>
#include <cctype>
#include <map>
#include <sstream>

LinearAllocator::LinearAllocator(size_t maxSize):maxSize(maxSize),volume(maxSize)
{
    if (maxSize == 0)
        base = nullptr;
    else
        base = (char*)malloc(maxSize*sizeof(char));
    pointer = base;

}

char* LinearAllocator::allocator(size_t size)
{
    if (size > volume)
        throw std::invalid_argument("Problem in allocation");  
    else 
    {   
        char* tmp = pointer;
        pointer = pointer + size*sizeof(char);
        volume = volume - size;
        return tmp;
    }
}

void LinearAllocator::reset()
{
    pointer = base;
    volume = maxSize;
}

size_t LinearAllocator::get_maxSize()
{
    return maxSize;
}

size_t LinearAllocator::get_volume()
{
    return volume;
}

LinearAllocator::~LinearAllocator()
{
    free(base);
}
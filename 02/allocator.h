#pragma once
#include <cstdio>
#include <cstdlib>

// size_t - базовый беззнаковый целочисленный тип языка Си/Си++
// Является типом результата, возвращаемого оператором sizeof.

class LinearAllocator
{
private:
    size_t maxSize;
    size_t volume;
    char* base;
    char* pointer;
    
public:
    LinearAllocator(size_t maxSize);
    char* allocator(size_t size);
    void reset();
    size_t get_maxSize();
    size_t get_volume();
    ~LinearAllocator();
};
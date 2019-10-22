#include "allocator.h"
#include <cstdio>
#include <iostream>
#include <string>
#include <cstdint>
#include <cctype>
#include <map>
#include <sstream>

int main(int argc, char const *argv[]) 
{
    try
    {
        if (argc < 2) 
            throw std::invalid_argument("No argument");  
        LinearAllocator creature(atoi (argv[1]));
        char *tmp = creature.allocator(1), *pointer;
        creature.reset();
        for (int i = 2; i < argc; i++)
        {
            switch (argv[i][0])
            {
                case 'a':
                    pointer = creature.allocator (atoi (argv[i] + 1));
                    if (pointer == nullptr)
                        throw std::invalid_argument("Nullptr");
                    else
                        std::cout << pointer - tmp << std::endl;
                    break;
                case 'r':
                    creature.reset ();
                    break;
                default:
                    i = argc;
            }
        }
        return 0;
    }
    catch (std::invalid_argument&exception) 
    {
        std::cout << exception.what() << std::endl;
        return 1;
    }
    
}
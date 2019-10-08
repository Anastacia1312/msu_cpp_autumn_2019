#include <chrono>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>


class Timer
{
    using clock_t = std::chrono::high_resolution_clock;
    using microseconds = std::chrono::microseconds;
public:
    Timer()
        : start_(clock_t::now())
    {
    }

    ~Timer()
    {
        const auto finish = clock_t::now();
        const auto us = std::chrono::duration_cast<microseconds> (finish - start_).count();
        std::cout << us << " us" << std::endl;
    }

private:
    const clock_t::time_point start_;
};


int main()
{
    int n = 10000;
    int m = 10000;
    
    int** arr = new int*[n];
    for(int i = 0; i < n; i++) 
        arr[i] = new int[m];
    
    for (int i = 0; i < n; i++) 
        for (int j = 0; j < m; j++) 
            arr[i][j] = i*i - 10*(i-j);
    
    Timer t;
    int s = 0;
    for (int j = 0; j < m; j++) 
        for (int i = 0; i < n; i++) 
            s = s + arr[i][j];
    
    for (int i = 0; i < n; i++) 
        delete[] arr[i];
    delete[] arr;
    
    return 0;
}
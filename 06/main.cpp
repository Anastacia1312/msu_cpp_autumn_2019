#include <iostream>
#include <sstream>
#include <cassert>
#include <stdexcept>
#include "format.h"
using namespace std;
int main()
{
    
    auto text = format("{1}+{1} = {0}", 2, "one");
    assert (text == "one+one = 2");
    
    
    try
    {
        text = format("{a} == 1", 1, 2, 3);
    }
    catch (runtime_error& error)
    {
        string s = error.what();
        assert (s == "invalid expression");
    }
    
    
    try
    {
        text = format("{0}+{0 = 0", "zero");
    }
    catch (runtime_error& error)
    {
        string s = error.what();
        assert (s == "no closing bracket");
    }
    
    
    try
    {
        text = format("{0}+{1} = 1", "zero");
    }
    catch (runtime_error& error)
    {
        string s = error.what();
        assert (s == "value in brackets is bigger than number of arguments");
    }
    

    try
    {
        text = format("}{");
    }
    catch (runtime_error& error)
    {
        string s = error.what();
            assert (s == "} before {");
    }

    cout << "Ok" << endl;
    return 0;
}
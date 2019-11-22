#pragma once
#include <stdexcept>
#include <vector>
using std::string;

class Format {
    
private:
    size_t n;
    string str;
    std::stringstream arg;
    std::vector<string> args;
    
public:
    
    Format(const char *str) : n(0), str(str){}
    
    size_t index(string::iterator& s, const string::iterator& end)
    {
        if (!std::isdigit(*s))
            throw std::runtime_error("invalid expression");
        size_t ind = 0;
        while(std::isdigit(*s) && (s != end)) 
        {
            ind *= 10;
            ind += *s - '0';
            s++;
        }
        if (*s != '}')
            throw std::runtime_error("no closing bracket");
        return ind;
    }
    
    template<typename T>
    void write(T&& arg)
    {
        n++;
        this->arg << arg;
        this->args.push_back(this->arg.str());
        this->arg.str(std::string());
    }
    
    template<typename T, typename... Args>
    void write(T&& arg, Args&&... args)
    {
        n++;
        this->arg << arg;
        this->args.push_back(this->arg.str());
        this->arg.str(string());
        write(std::forward<Args>(args)...);
    }
    
    string format_answer()
    {
        string ans;
        for (auto s = str.begin(); s != str.end(); ++s)
        {
            if (*s =='{')
            {
                s++;
                size_t ind = index(s, str.end());
                if (ind > n-1)
                    throw std::runtime_error("value in brackets is bigger than number of arguments");
                ans += args[ind];
            } 
            else
            {
                if (*s =='}')
                    throw std::runtime_error("} before {");
                ans += *s;
            }
        }
        return ans;
    }
};

template<typename... Args>
string format(const char* str, Args&&... args)
{
    Format ans(str);
    ans.write(std::forward<Args>(args)...);
    return ans.format_answer();
}

string format(const char* str)
{
    Format ans(str);
    return ans.format_answer();
}


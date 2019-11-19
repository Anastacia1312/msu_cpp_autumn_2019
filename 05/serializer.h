#pragma once
#include <sstream>


enum class Error
{
    NoError,
    CorruptedArchive
};



class Serializer
{
    static constexpr char Separator = ' '; 

public:

    explicit Serializer(std::ostream& out) : out_(out) {}

    template <class T>
    Error save(T& object)
    {
        return object.serialize(*this);
    }

    template <class... ArgsT>
    Error operator()(ArgsT&&... args)
    {
        return process(std::forward<ArgsT>(args)...);
    }
    
private:
    // process использует variadic templates
    std::ostream& out_;

    template <class T, class... ArgsT>
    Error process(T&& arg, ArgsT&&... args)
    {
        func(arg);
        return process(std::forward<ArgsT>(args)...);
    }

    template <class T>
    Error process(T&& arg)
    {
        func(arg);
        return Error::NoError;
    }
    
    void func(uint64_t arg)
    {
        out_ << arg << Separator;
    }

    void func(bool arg)
    {
        if (arg)
            out_ << "true" << Separator;
        else
            out_ << "false" << Separator;
    }
};





class Deserializer
{
    static constexpr char Separator = ' ';

public:
    
    explicit Deserializer(std::istream& in) : in_(in) {}

    template <class T>
    Error load(T& object)
    {
        return object.deserialize(*this);
    }

    template <class... ArgsT>
    Error operator()(ArgsT&&... args)
    {
        return process(std::forward<ArgsT>(args)...);
    }
    
private:
    
    std::istream& in_;

    template <class T, class... ArgsT>
    Error process(T&& value, ArgsT&&... args)
    {
        if (load(value) == Error::CorruptedArchive)
            return Error::CorruptedArchive;
        else
            return process(std::forward<ArgsT>(args)...);
    }

    template <class T>
    Error process(T&& value)
    {
        return load(value);
    }
    
    Error load(bool& value)
    {
        std::string text;
        in_ >> text;
        
        if (text == "true")
            value = true;
        else if (text == "false")
            value = false;
        else
            return Error::CorruptedArchive;
        
        return Error::NoError;
    }
    
    Error load(uint64_t& value)
    {
        std::string text;
        in_ >> text;
        
        for (size_t i = 0; i < text.length(); i++)
            if (!std::isdigit(text[i]))
                return Error::CorruptedArchive;
        value = std::stoull(text);
        
        return Error::NoError;
    }

};
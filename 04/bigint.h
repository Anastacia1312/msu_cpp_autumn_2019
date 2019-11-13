#pragma once
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>

class BigInt
{
private:
    char* numbers;
    bool sign; //true - negative, false - positive
    size_t size;
    
public:
    BigInt();
    BigInt(int number);
    BigInt(const std::string& s);
    BigInt(const BigInt& n);
    BigInt(BigInt&& moved);
    BigInt& operator=(const BigInt& n);
    BigInt& operator=(BigInt&& moved);
    BigInt operator-() const;
    bool operator==(const BigInt& n) const;
    bool operator!=(const BigInt& n) const;
    bool operator<(const BigInt& n) const;
    bool operator<=(const BigInt& n) const;
    bool operator>(const BigInt& n) const;
    bool operator>=(const BigInt& n) const;
    friend BigInt operator+(const BigInt& n1, const BigInt& n2);
    friend BigInt operator-(const BigInt& n1, const BigInt& n2);
    friend std::ostream& operator<<(std::ostream& out, const BigInt& n);
    ~BigInt();
};
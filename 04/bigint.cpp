#include "bigint.h"

BigInt::BigInt(): sign(false), numbers(nullptr), size(0) 
{
}

BigInt::BigInt(int number): sign(number<0)
{
    std::string str;
    str = std::to_string(abs(number));
    size = str.length();
    numbers = new char [size];
    for (size_t i = 0; i < size; i++)
        numbers[i] = str[i];
}

BigInt::BigInt(const std::string& s)
{
    std::string str;
    str = s;
    size = str.length();
    if (str[0] == '-')
    {
        sign = true;
        size -= 1;
        str = str.substr(1);
    }
    else
        sign = false;
    numbers  = new char[size];
    for (size_t i = 0; i < size; i++ )
        numbers[i] = str[i];
}

BigInt::BigInt(const BigInt& n): sign(n.sign), size(n.size)
{
    numbers = new char [size];
    std::memcpy(numbers, n.numbers, size);
}

BigInt::BigInt(BigInt&& moved)
{
    numbers = moved.numbers;
    moved.numbers = nullptr;
    sign = moved.sign;
    moved.sign = false;
    size = moved.size;
    moved.size = 0;
}

BigInt& BigInt::operator=(const BigInt& n)
{
    if (this == &n)
        return *this;
    else 
    {
        sign = n.sign;
        size = n.size;
        delete [] numbers;
        numbers = new char[size];
        std::memcpy(numbers, n.numbers, size);
        return *this;
    }
}

BigInt& BigInt::operator=(BigInt&& moved)
{
    if (this == &moved)
        return *this;
    else
    {
        sign = moved.sign;
        moved.sign = false;
        size = moved.size;
        moved.size = 0;
        delete [] numbers;
        numbers = moved.numbers;
        moved.numbers = nullptr;
        return *this;
    }
}

BigInt BigInt::operator-() const 
{
    BigInt n = *this;
    n.sign = !(this->sign);
    return n;
}

bool BigInt::operator==(const BigInt& n) const
{
    if ((sign==n.sign) && (size==n.size))
    {
        for(size_t i = 0; i < size; i++)
            if (numbers[i] != n.numbers[i])
                return false;
        return true;
    }
    else
        return false;
}

bool BigInt::operator!=(const BigInt& n) const
{
    return !(*this==n);
}

bool BigInt::operator<(const BigInt& n) const
{
    bool b = false;
    if (sign == n.sign)
    {
        if (size == n.size)
        {
            for (size_t i = 0; i < size; i++)
            {
                if (numbers[i] > n.numbers[i])
                {
                    b = true;
                    break;
                }
                if (numbers[i] < n.numbers[i])
                    break;
            }
        }
        else
            b = (size > n.size);
        return (sign==b);
    }
    else 
        return sign;
}

bool BigInt::operator<=(const BigInt& n) const
{
    return ((*this<n)||(*this==n));
}

bool BigInt::operator>(const BigInt& n) const
{
    return !(*this<=n);
}

bool BigInt::operator>=(const BigInt& n) const
{
    return !(*this<n);
}

BigInt operator+(const BigInt& n1, const BigInt& n2)
{
    size_t n = 0; //для первых нулей, образующихся при вычитании
    //оба положительные
    if ((n1.sign==false) && (n2.sign==false))
    {
        size_t size = n1.size > n2.size ? n1.size+1 : n2.size+1;
        int* arr = new int[size];
        for (size_t i = 0; i < size; i++) arr[i] = 0;
        for (size_t i = 0; i < size-1; i++)
        {
            if (n1.size >= i+1)
                arr[size-i-1] += (n1.numbers[n1.size-i-1] - '0');
            if (n2.size >= i+1)
                arr[size-i-1] += (n2.numbers[n2.size-i-1] - '0');
            if (arr[size-i-1]>9)
            {
                arr[size-i-2] = 1;
                arr[size-i-1] -= 10;
            }
        }
        BigInt sum;
        sum.sign = false;
        sum.size = size;
        size_t k = 0;
        if (arr[0]==0)
        {
            sum.size -= 1;
            k = 1;
        }
        sum.numbers = new char[sum.size];
        for (size_t i = 0; i < sum.size; i++)
            sum.numbers[i] = arr[i+k] + '0';
        delete [] arr;
        return sum;
    }
    
    //оба отрицательные
    if (n1.sign==true && n2.sign==true)
        return -((-n1)+(-n2));
    
    //остались разных знаков
    if (n1.size > n2.size)
    {
        size_t size = n1.size;
        int* arr = new int[size];
        for (size_t i = 0; i < size; i++) arr[i] = n1.numbers[i] - '0';
        for (size_t i = 0; i < n2.size; i++)
        {
            if (arr[size-i-1] >= n2.numbers[n2.size-i-1] - '0')
                arr[size-i-1] -= n2.numbers[n2.size-i-1] - '0';
            else
            {
                arr[size-i-1] += 10;
                arr[size-i-1] -= n2.numbers[n2.size-i-1] - '0';
                arr[size-i-2] -=1;
            }
        }
        for (size_t i = 0; i < size; i++)
        {
            if (arr[i] == 0)
                n += 1;
            else 
                break;
        }
        BigInt sum;
        sum.sign = n1.sign;
        sum.size = size - n;
        sum.numbers = new char[sum.size];
        for (size_t i = 0; i < sum.size; i++)
            sum.numbers[i] = arr[i + n] + '0';
        delete [] arr;
        return sum;
    }
    
    if (n1.size < n2.size)
    {
        size_t size = n2.size;
        int* arr = new int[size];
        for (size_t i = 0; i < size; i++) arr[i] = n2.numbers[i] - '0';
        for (size_t i = 0; i < n1.size; i++)
        {
            if (arr[size-i-1] >= n1.numbers[n1.size-i-1] - '0')
                arr[size-i-1] -= n1.numbers[n1.size-i-1] - '0';
            else
            {
                arr[size-i-1] += 10;
                arr[size-i-1] -= n1.numbers[n1.size-i-1] - '0';
                arr[size-i-2] -=1;
            }
        }
        for (size_t i = 0; i < size; i++)
        {
            if (arr[i] == 0)
                n += 1;
            else 
                break;
        }
        BigInt sum;
        sum.sign = n2.sign;
        sum.size = size - n;
        sum.numbers = new char[sum.size];
        for (size_t i = 0; i < sum.size; i++)
            sum.numbers[i] = arr[i + n] + '0';
        delete [] arr;
        return sum;
    }
       
    if (n1.size == n2.size && ((!n1.sign && n1>=-n2)||(n1.sign  && -n1>=n2)))
    {
        size_t size = n1.size + 1;
        int* arr = new int[size];
        arr[0] = 1;
        for (size_t i = 1; i < size; i++) 
            arr[i] = n1.numbers[i-1] - '0';
        for (size_t i = 0; i < n2.size; i++)
        {
            if (arr[size-i-1] >= n2.numbers[n2.size-i-1] - '0')
                arr[size-i-1] -= n2.numbers[n2.size-i-1] - '0';
            else
            {
                arr[size-i-1] += 10 - n2.numbers[n2.size-i-1] - '0';
                arr[size-i-2] -=1;
            }
        }
        for (size_t i = 1; i < size; i++)
        {
            if (arr[i] == 0)
                n += 1;
            else 
                break;
        }
        BigInt sum;
        sum.size = size-1-n;
        sum.sign = n1.sign;
        sum.numbers = new char[sum.size];
        for (size_t i = 0; i < sum.size; i++)
            sum.numbers[i] = arr[i+1+n] + '0';
        delete [] arr;
        return sum;
    }
    else 
    {
        size_t size = n1.size + 1;
        int* arr = new int[size];
        arr[0] = 1;
        for (size_t i = 1; i < size; i++) 
            arr[i] = n2.numbers[i-1] - '0';
        for (size_t i = 0; i < n1.size; i++)
        {
            if (arr[size-i-1] >= n1.numbers[n1.size-i-1] - '0')
                arr[size-i-1] -= n1.numbers[n1.size-i-1] - '0';
            else
            {
                arr[size-i-1] += 10 - n1.numbers[n1.size-i-1] - '0';
                arr[size-i-2] -=1;
            }
        }
        BigInt sum;
        sum.size = size-1;
        sum.sign = n2.sign;
        sum.numbers = new char[sum.size];
        for (size_t i = 0; i < sum.size; i++)
            sum.numbers[i] = arr[i+1] + '0';
        delete [] arr;
        return sum;
    }
}

BigInt operator-(const BigInt& n1, const BigInt& n2)
{
    return n1+(-n2);
}

std::ostream& operator<<(std::ostream &out, const BigInt& n)
{
    if (n.sign)
        out << '-';
    for (size_t i = 0; i < n.size; i++)
        out << n.numbers[i];
    out << std::endl;
    return out;
}

BigInt::~BigInt()
{
    delete [] numbers;
}
#include <cassert>
#include "bigint.h"
using namespace std;

int main()
{
    BigInt a = 111;
    BigInt b = 222;
    assert(a + b == 333);
    assert(a - b == -111);
    assert(b - a == 111);
    assert(-b - a == -333);
    
    BigInt d = -1000;
    BigInt e = 200;
    assert(d + e == -800);
    assert(d - e == -1200);
    assert(e - d == 1200);
    assert(-e - d == 800);
    
    BigInt x("10000000000000000000000000000000000000000000000000000000000");
    BigInt y("20000000000000000000000000000000000000000000000000000000000");
    assert(x != y);
    assert(x < y);
    assert(x <= y);
    assert(y >= x);
    assert(y > x);
    assert(y > -x);
    assert(x > -y);
    assert(-y < -x);
    
    cout << x << endl;
    cout << y << endl;
    x = y;
    cout << x << endl;
    assert(x==y);
    cout << x << endl;

    cout << "Ok" << endl;
    return 0;
}
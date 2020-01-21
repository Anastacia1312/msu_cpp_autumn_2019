#include <iostream>
#include "vector.h"
#include <algorithm>
#include <cassert>

using std::string;
using std::cout;
using std::endl;
int main()
{
    Vector<int> example;
    for (size_t i = 0; i < 10; ++i) {
        example.push_back(10-i);
    }
    assert(example.size() == 10);
    assert(!example.empty());
    cout << "before pop_back";
    cout << endl;
    for (auto it = example.begin(); it < example.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    example.pop_back();
    cout << "after pop_back";
    cout << endl;
    for (auto it = example.rbegin(); it != example.rend(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    assert(example.size() == 9);
    assert(!example.empty());

    cout << "after sort";
    cout << endl;
    std::sort(example.begin(), example.end());
    for (auto it : example) {
        cout << it  << " ";
    }
    cout << endl;
    example.clear();
    assert(example.empty());
    cout << "Ok" << endl;
    return 0;
}
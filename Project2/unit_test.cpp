#include "src/number.cpp"
#include <iostream>
#include <string>
#include <cstring>

using std::cout;
using std::endl;

int test() {
    string s = "-0.1234567";
    long double ld = 12345.67;
    number a, b;
    a = number(s);
    b = number(ld);

    for (int i = 0; i < a.length; i++)
        cout << a.digits[i];
    cout << " " << a.expo << " " << a.is_negtive << endl;

    for (int i = 0; i < b.length; i++)
        cout << b.digits[i];
    cout << " " << b.expo << endl;

    return 0;
}
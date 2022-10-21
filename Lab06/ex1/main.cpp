#include <iostream>
#include "libswap.h"

using std::cout;
using std::endl;

int main() {
    int a, b;
    
    a = 1, b = 2;
    int_swap(a, b);
    cout << a << " " << b << endl;

    a = 1, b = 2;
    ptr_swap(&a, &b);
    cout << a << " " << b << endl;

    a = 1, b = 2;
    ref_swap(a, b);
    cout << a << " " << b << endl;

    return 0;
}
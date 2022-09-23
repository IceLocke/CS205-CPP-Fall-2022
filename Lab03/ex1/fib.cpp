#include "fib.hpp"

int fib(int n) {
    int a = 1, b = 1, c;
    if (n == 1 || n == 2)
        return 1;
    for (int i = 3; i <= n; i++) {
        c = a + b;
        a = b, b = c;
    }
    return c;
}
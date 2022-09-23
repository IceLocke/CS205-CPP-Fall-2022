#include <iostream>
#include <cstdio>
#include "fac.hpp"

void int128_print(__int128 x) {
    char stack[40];
    int p = 0;

    while (x > 0) {
        stack[p++] = (int)((x % 10)) + '0';
        x /= 10; 
    }

    while (p) putchar(stack[--p]);
} 

int main() {

    int n = 0;

    while (n <= 0) {
        std::cout << "Please input a postive integer: ";
        std::cin >> n;
    }

    for (int i = 1; i <= n; i++) {
        std::cout << i << "! = ";
        int128_print(fac(i));
        std::cout << std::endl;
    }

    return 0;
}
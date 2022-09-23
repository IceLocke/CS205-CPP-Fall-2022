#include <iostream>
#include "fib.hpp"


int main() {

    int n = 0;

    while (n <= 0) {
        std::cout << "Please input a postive integer: ";
        std::cin >> n;
    }

    for (int i = 1; i <= n; i++) {
        std::cout << fib(i) << " ";
        if (i % 10 == 0) std::cout << std::endl;
    }

    std::cout << std::endl;

    return 0;
}
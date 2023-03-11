#include "complex.hpp"
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int main() {
    Complex a = Complex(1.0, -1.0);
    Complex b = Complex(1.0, 2.0);
    Complex c;
    c = a + b;
    cout << c << endl;
    c = a - b;
    cout << c << endl;
    c = a * b;
    cout << c << endl;
    cout << (a == b) << endl << (a != b) << endl;
    cin >> c;
    cout << c << endl;
}
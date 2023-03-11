#include "complex.hpp"

int main() {
    Complex a = Complex(1.0, -1.0);
    Complex b = Complex(1.0, 2.0);
    Complex c;
    c = a + b;
    c.show();
    c = a - b;
    c.show();
}
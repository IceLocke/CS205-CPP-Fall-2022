#include "complex.hpp"
#include <iostream>

using std::cout;
using std::endl;

Complex Complex::operator + (Complex &c) {
    double real = this->getRealPart() + c.getRealPart(),
           imag = this->getImagPart() + c.getImagPart();
    Complex res = Complex(real, imag);
    return res;
}

Complex Complex::operator - (Complex &c) {
    double real = this->getRealPart() - c.getRealPart(),
           imag = this->getImagPart() - c.getImagPart();
    Complex res = Complex(real, imag);
    return res;
}

void Complex::show() {
    cout << (this->getRealPart()) << (this->getImagPart() > 0 ? "+" : "") << this->getImagPart() << 'i';
    cout << endl;
}

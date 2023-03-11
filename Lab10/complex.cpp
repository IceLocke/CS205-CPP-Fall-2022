#include "complex.hpp"
#include <iostream>
#include <cmath>

using std::cout;
using std::endl;

const double EPS = 1e-9;

Complex Complex::operator+ (Complex const &c) const {
    double real = this->getRealPart() + c.getRealPart(),
           imag = this->getImagPart() + c.getImagPart();
    Complex res = Complex(real, imag);
    return res;
}

Complex Complex::operator- (Complex const &c) const {
    double real = this->getRealPart() - c.getRealPart(),
           imag = this->getImagPart() - c.getImagPart();
    Complex res = Complex(real, imag);
    return res;
}

Complex Complex::operator* (Complex const &c) const {
    double real = this->getRealPart() * c.getRealPart() - this->getImagPart() * c.getImagPart(),
           imag = this->getImagPart() * c.getRealPart() + this->getRealPart() * c.getImagPart();
    Complex res = Complex(real, imag);
    return res;
}

Complex & Complex::operator= (Complex c) {
    this->setRealPart(c.getRealPart());
    this->setImagPart(c.getImagPart());
    return *this;
}

bool Complex::operator== (Complex const &c) const {
    return (fabs(this->getRealPart() - c.getRealPart()) < EPS) &&
           (fabs(this->getImagPart() - c.getImagPart()) < EPS);
}

bool Complex::operator!= (Complex const &c) const {
    return !((fabs(this->getRealPart() - c.getRealPart()) < EPS) &&
            (fabs(this->getImagPart() - c.getImagPart()) < EPS));
}

std::ostream & operator<< (std::ostream &os, Complex const &c) {
    os << c.getRealPart() << (c.getImagPart() > 0 ? "+" : "") << c.getImagPart() << "i";
    return os;
}

std::istream & operator>> (std::istream &is, Complex &c) {
    double real, imag;
    is >> real >> imag;
    c.setRealPart(real), c.setImagPart(imag);
    return is;
}

void Complex::show() {
    cout << (this->getRealPart()) << (this->getImagPart() > 0 ? "+" : "") << this->getImagPart() << 'i';
    cout << endl;
}

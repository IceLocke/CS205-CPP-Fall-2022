#pragma once
#include <iostream>

class Complex {
    private:
        double real;
        double imag;
    public:
        void setRealPart(double real) {
            this->real = real;
        }
        void setImagPart(double imag) {
            this->imag = imag;
        }
        double getRealPart() const {
            return real;
        }
        double getImagPart() const {
            return imag;
        }
        Complex(double real, double imag) {
            this->real = real;
            this->imag = imag;
        }
        Complex() {
            this->real = 0.0, this->imag = 0.0;
        }
        Complex operator+ (Complex const &c) const;
        Complex operator- (Complex const &c) const;
        Complex operator* (Complex const &c) const;
        Complex & operator= (Complex c);
        bool operator== (Complex const &c) const;
        bool operator!= (Complex const &c) const;
        friend std::ostream & operator<< (std::ostream &os, Complex const &c);
        friend std::istream & operator>> (std::istream &is, Complex &c);
        void show();
};
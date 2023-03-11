#pragma once

class Complex {
    private:
        double real;
        double imag;
    public:
        double getRealPart() {
            return real;
        }
        double getImagPart() {
            return imag;
        }
        Complex(double real, double imag) {
            this->real = real;
            this->imag = imag;
        }
        Complex() {
            this->real = 0.0, this->imag = 0.0;
        }
        Complex operator+ (Complex &c);
        Complex operator- (Complex &c);
        void show();
};
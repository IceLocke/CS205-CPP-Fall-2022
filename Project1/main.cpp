// Copyright 2022 Gong Linghu
// License(MIT)
// Author: Gong Linghu
// A simple calculater which can multiply two numbers. Implement by FFT.

#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <vector>
#include <ctype.h>

using std::cout;
using std::endl;
using std::abs;
using std::string;

const int MAXN = 4 * 6e4 + 10;
const double PI = acos(-1.0);

struct Complex {
    double real, imag;
    Complex(double x = 0.0, double y = 0.0) {
        real = x, imag = y;
    }
    inline Complex getConj () {
        return Complex(this->real, -this->imag);
    }
};

inline Complex operator +(Complex a, Complex b) {
        return Complex(a.real + b.real, a.imag + b.imag);
    }
inline Complex operator -(Complex a, Complex b) {
    return Complex(a.real - b.real, a.imag - b.imag);
}
inline Complex operator *(Complex a, Complex b) {
    return Complex(a.real * b.real - a.imag * b.imag, 
                    a.real * b.imag + a.imag * b.real);
}

template <typename T>
inline void swap(T &x, T &y) {
    T t = x;
    x = y;
    y = t;
}

int len, n = 1, lim, 
    a_len, b_len, 
    a_point, b_point,
    a_exp, b_exp;

bool a_neg = false, b_neg = false;

Complex a[MAXN], b[MAXN];

void fft(Complex *a, bool inv) {
    lim = 0;
    while ((1 << lim) < n)
        lim++;
    
    for (register int i = 0; i < n; i++) {
        register int t = 0;
        for (register int j = 0; j < lim; j++)
            if ((i >> j) & 1)
                t |= (1 << (lim - j - 1));
        if (i < t)
            swap(a[i], a[t]);
    }
    
    for (register int l = 2; l <= n; l <<= 1) {
        int m = l >> 1;
        Complex wn(cos(2 * PI / l), sin(2 * PI / l));
        if (inv)
            wn = wn.getConj();
        for (register Complex *p = a; p != a + n; p += l) {
            register Complex w(1.0, 0.0);
            for (register int i = 0; i < m; i++) {
                register Complex t = w * p[i + m];
                p[i + m] = p[i] - t;
                p[i] = p[i] + t;
                w = w * wn;
            }
        }
    } 
}

void multiply() {
    while (n < a_len + b_len)
        n <<= 1;
    
    fft(a, 0);
    fft(b, 0);
    
    for (register int i = 0; i < n; i++)
        a[i] = a[i] * b[i];
        
    fft(a, 1);
    
    for (register int i = 0; i < n; i++)
        a[i].real = a[i].real / (double)n;
    
    for (register int i = 0; i < n; i++) {
        if(!(a[i].real <= 9)) {
            a[i + 1].real += (int)(a[i].real + 0.5) / 10;
            a[i].real = a[i].real - ((int)(a[i].real + 0.5) / 10) * 10;   
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        cout << "Invalid input length!" << endl;
        return 0;
    }
    else {
        std::vector<int> num;

        a_len = 0, b_len = 0;
        a_exp = 0, b_exp = 0;
        a_point = -1, b_point = -1;

        // Input of A
        char *p = argv[1];
        bool is_exp = false, neg_exp = false;
        while (*p != '\0') {
            if (isdigit(*p)) {
                if (!is_exp) num.push_back(*p - '0');
                else a_exp = a_exp * 10 + (*p - '0');
            }
            else if (*p == '.') a_point = num.size();
            else if (*p == 'e') is_exp = true;
            else if (*p == '-') {
                if (!is_exp) a_neg = true;
                else neg_exp = true;
            }
            else {
                cout << "The input cannot be interpret as numbers!" << endl;
                return 0;
            }
            ++p;
        }
        if (neg_exp) a_exp *= -1;
        if (is_exp == true && a_exp == 0) {
            cout << "The input cannot be interpret as numbers!" << endl;
            return 0;
        }

        // deal with exp relations
        if (a_point == -1)
            a_point = num.size();
        a_len = num.size();
        a_exp += a_point - a_len;

        // reversed input
        int flag = 0;
        while (num[flag] == 0) ++flag;
        for (register int i = flag; i < a_len; i++)
            a[a_len - flag - i - 1].real = (double)num[i];

        // Input of B
        p = argv[2];
        is_exp = false, neg_exp = false;
        num.clear();
        while (*p != '\0') {
            if (isdigit(*p)) {
                if (!is_exp) num.push_back(*p - '0');
                else b_exp = b_exp * 10 + (*p - '0');
            }
            else if (*p == '.') b_point = num.size();
            else if (*p == 'e') is_exp = true;
            else if (*p == '-') {
                if (!is_exp) b_neg = true;
                else neg_exp = true;
            }
            else {
                cout << "The input cannot be interpret as numbers!" << endl;
                return 0;
            }
            ++p;
        }
        if (neg_exp) b_exp *= -1;
        cout << b_exp << endl;
        if (is_exp == true && b_exp == 0) {
            cout << "The input cannot be interpret as numbers!" << endl;
            return 0;
        }

        // same as above
        if (b_point == -1)
            b_point = num.size();
        b_len = num.size();
        b_exp += b_point - b_len;

        flag = 0;
        while (num[flag] == 0) ++flag;
        for (register int i = flag; i < b_len; i++)
            b[b_len - flag - i - 1].real = (double)num[i];
    }

    cout << endl;
	for (int i = 0; i < 10; i++)
		cout << a[i].real;
	cout << endl;
	for (int i = 0; i < 10; i++)
		cout << b[i].real;
	cout << endl;
	 
    multiply();

    // remove prefix zeros
    int flag = n - 1;
    while (fabs(a[flag].real) <= 0.50000)
        flag--;

	cout << flag << endl;

    char *p = argv[1];
    while (*p != '\0') cout << *p++;
    cout << " * ";
    p = argv[2];
    while (*p != '\0') cout << *p++;
    cout << " = ";

    // if too much digits, use scientific
    if (abs(a_exp + b_exp) > 20) {
        int exp_sum = a_exp + b_exp + (flag);
        for (register int i = flag; i >= 0; i--) {
            cout << (int)(a[i].real + 0.5);
            if (i == flag)
                cout << '.';
        }
        cout << 'e' << exp_sum;
    }
    else {
        
        for (register int i = flag; i >= 0; i--) {
            cout << (int)(a[i].real + 0.5);
            if (-i == a_exp + b_exp && i != 0)
                cout << '.';
        }
        if (a_exp + b_exp > 0)
            for (register int i = 1; i <= a_exp + b_exp; i++)
                cout << 0;
    }
    cout << endl;
    
    return 0;
}
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
    a_exp = 0, b_exp = 0;

bool a_neg = false, b_neg = false;

Complex a[MAXN], b[MAXN];

// 快速傅里叶变换，
void fft(Complex *a, bool inv) {
    lim = 0;
    while ((1 << lim) < n)
        lim++;
    
    // 蝴蝶变换，自底向上处理
    for (register int i = 0; i < n; i++) {
        register int t = 0;
        for (register int j = 0; j < lim; j++)
            if ((i >> j) & 1)
                t |= (1 << (lim - j - 1));
        if (i < t)
            swap(a[i], a[t]);
    }
    
    // 迭代处理
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
    
    // 将大于9的多项式系数前移
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

        // A的输入部分，需要在多处检查输入合法性
        char *p = argv[1];
        bool is_exp = false, neg_exp = false;
        while (*p != '\0') {
            if (isdigit(*p)) {
                if (!is_exp) num.push_back(*p - '0');
                else a_exp = a_exp * 10 + (*p - '0');
            }
            else if (*p == '.' && a_point == -1) a_point = num.size();
            else if ((*p == 'e' || *p == 'E') && !is_exp) is_exp = true;
            else if (*p == '-' && (num.size() == 0 || (is_exp && a_exp == 0)))
            {
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
        if (is_exp && a_exp == 0) {
            cout << "The input cannot be interpret as numbers!" << endl;
            return 0;
        }

        // 将小数全部转为整数+指数的形势
        if (a_point == -1)
            a_point = num.size();
        a_len = num.size();
        a_exp += a_point - a_len;

        // 倒序存储，便于FFT计算
        int flag = 0;
        while (num[flag] == 0) ++flag;
        for (register int i = flag; i < a_len; i++)
            a[a_len - i - 1].real = (double)num[i];

        // B的输入部分，同上
        p = argv[2];
        is_exp = false, neg_exp = false;
        num.clear();
        while (*p != '\0') {
            if (isdigit(*p)) {
                if (!is_exp) num.push_back(*p - '0');
                else b_exp = b_exp * 10 + (*p - '0');
            }
            else if (*p == '.' && b_point == -1) b_point = num.size();
            else if ((*p == 'e' || *p == 'E') && !is_exp) is_exp = true;
            else if (*p == '-' && (num.size() == 0 || (is_exp && b_exp == 0)))
            {
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
        if (is_exp && b_exp == 0) {
            cout << "The input cannot be interpret as numbers!" << endl;
            return 0;
        }
        if (b_point == -1)
            b_point = num.size();
        b_len = num.size();
        b_exp += b_point - b_len;

        flag = 0;
        while (num[flag] == 0) ++flag;
        for (register int i = flag; i < b_len; i++)
            b[b_len - i - 1].real = (double)num[i];
    }
	 
    multiply();

    // 删除前缀和后缀0
    int pre_flag = n - 1;
    while (fabs(a[pre_flag].real) <= 0.50000) pre_flag--;
    int suf_flag = 0;
    while (fabs(a[suf_flag].real) <= 0.50000) suf_flag++;

    char *p = argv[1];
    while (*p != '\0') cout << *p++;
    cout << " * ";
    p = argv[2];
    while (*p != '\0') cout << *p++;
    cout << " = ";

    if (a_neg ^ b_neg) cout << '-';

    // 判断有效位数，如果过多采用科学计数法
    int exp_sum = a_exp + b_exp + suf_flag;
    if (abs(exp_sum) > 20 || (pre_flag - suf_flag) > 20) {
        for (register int i = pre_flag; i >= suf_flag; i--) {
            cout << (int)(a[i].real + 0.5);
            if (i == pre_flag && i != suf_flag)
                cout << '.';
        }
        if (exp_sum != 0)
            cout << 'e' << exp_sum;
    }
    else {
        if (exp_sum < 0 && abs(exp_sum) - pre_flag >= 0) {
            cout << "0.";
            for (register int i = 1; i < abs(exp_sum) - pre_flag; i++)
                cout << 0;
        }
        for (register int i = pre_flag; i >= suf_flag; i--) {
            cout << (int)(a[i].real + 0.5);
            if (-i == a_exp + b_exp && i != suf_flag)
                cout << '.';
        }
        if (a_exp + b_exp > 0)
            for (register int i = 1; i <= a_exp + b_exp; i++)
                cout << 0;
    }
    cout << endl;
    
    return 0;
}
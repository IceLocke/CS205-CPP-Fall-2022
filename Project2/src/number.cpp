#include "../include/number.h"
#include <cmath>
#include <string>
#include <cstring>
#include <iostream>
#include <string.h>

using std::string;
using std::memset;
using std::to_string;
using std::log10;
using std::max;
using std::fmod;
using std::pow;
using std::cout;
using std::endl;

void number::print() {
    for (int i = 0; i < length; i++)
        cout << digits[i] << " ";
    cout << endl << "expo:" << expo << endl;
    return;
}

number::number () {
    memset(digits, 0, sizeof(digits));
}

number::number(string str) {
    memset(digits, 0, sizeof(digits));
    length = 0;
    for (int i = str.length() - 1; i >= 0; i--) {
        if (str[i] == '-')
            is_negtive = true;
        else if (str[i] == '.')
            expo = i;
        else digits[length++] = str[i] - '0';
    }
    if (expo != -1) expo = expo - length - is_negtive;
    else expo = 0;
}

number::number(long double lf) {
    memset(digits, 0, sizeof(digits));
    string str = std::to_string(lf);
    length = 0;
    for (int i = str.length() - 1; i >= 0; i--) {
        if (str[i] == '-')
            is_negtive = true;
        else if (str[i] == '.')
            expo = i;
        else digits[length++] = str[i] - '0';
    }
    if (lf < 0) is_negtive = true;
    if (expo != -1) expo = expo - length - is_negtive;
    else expo = 0;
}

// exists precision loss
long double number::to_longdouble() {
    long double res = 0.0;
    for (int i = length - 1; i >= 0; i--)
        res = res * 10.0 + digits[i];
    if (expo > 0)
        for (int i = 1; i <= expo; i++)
            res = res * 10.0;
    if (expo < 0)
        for (int i = 1; i <= -expo; i++)
            res = res / 10.0;
    return is_negtive ? res * -1.0 : res;
}

double number::to_double() {
    return to_longdouble();
}

string number::to_string() {
    int pre_flag = length;
    while (digits[pre_flag] == 0 && pre_flag >=0 ) pre_flag--;
    int suf_flag = 0;
    while (digits[suf_flag] == 0 && suf_flag < length) suf_flag++;
    string res;
    if (is_negtive)
        res.push_back('-');
    if (pre_flag <= suf_flag && digits[suf_flag] == 0) {
        res.push_back('0');
        return res;
    }
    if (expo < 0 && expo + (pre_flag + 1) <= 0) {
            res.append("0.");
            for (int i = 1; i <=  -expo  - (pre_flag + 1); i++)
                res.push_back('0');
        }
        for (int i = pre_flag; i >= suf_flag; i--) {
            res.push_back(digits[i] + '0');
            if (-i == expo && i != suf_flag)
                res.push_back('.');
        }
        if (expo > 0)
            for (int i = 1; i <= expo; i++)
                res.push_back('0');
    return res;
}

// add by padding
//  7654321.012
//   000076.54321123
number operator+ (number &a, number &b) {
    if (a.is_negtive == b.is_negtive) {
        number *x = a.expo < b.expo ? &a : &b, 
            *y = a.expo < b.expo ? &b : &a;
        number res;
        // padding zero for greater expo
        int distance = y->expo - x->expo;
        int res_len = max(x->length, y->length + distance) + 1;
        for (int i = 0; i < res_len; i++) {
            res.digits[i] += x->digits[i];
            if (i >= distance)
                res.digits[i] += y->digits[i - distance];
            if (res.digits[i] >= 10) {
                res.digits[i + 1]++;
                res.digits[i] %= 10;
            }
        }
        if (a.is_negtive)
            res.is_negtive = true;
        res.length = res_len;
        res.expo = x->expo;
        return res;
    }
    else
        return number(a.to_longdouble() + b.to_longdouble());
}

number operator- (number &a, number &b) {
    return number(a.to_longdouble() - b.to_longdouble());
}

number operator* (number &a, number &b) {
    number res;
    res.is_negtive = a.is_negtive ^ b.is_negtive;
    res.expo = a.expo + b.expo;
    res.length = a.length + b.length - 1;
    for (int i = 0; i < res.length; i++) {
        for (int j = 0; j <= i; j++)
            res.digits[i] += a.digits[j] * b.digits[i - j];
        if (res.digits[i] >= 10) {
            res.digits[i + 1] += res.digits[i] / 10;
            res.digits[i] %= 10;
        }
    }
    return res;
}

number operator/ (number &a, number &b) {
    return number(a.to_longdouble() / b.to_longdouble());
}

number operator% (number &a, number &b) {
    return number(fmod(a.to_longdouble(), b.to_longdouble()));
}

number operator^ (number &a, number &b) {
    return number(pow(a.to_longdouble(), b.to_longdouble()));
}
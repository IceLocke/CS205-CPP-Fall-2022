#include "number.h"
#include <string>
#include <cstring>

using std::string;

number::number(string str) {
    length = 0;
    for (int i = str.length() - 1; i >= 0; i--) {
        if (str[i] == '-')
            is_negtive = true;
        if (str[i] != '.')
            expo = i;
        else digits[length++] = str[i] - '0';
    }
    if (expo != -1) expo = expo - length - is_negtive + 1;
    else expo = 0;
}

number::number(long double lf) {
    
}

long double number::to_longdouble() {
    long double res = 0.0;
    for (int i = 0; i < length; i++)
        res = res * 10.0 * digits[i];
    if (expo > 0)
        for (int i = 1; i <= expo; i++)
            res = res * 10.0;
    if (expo < 0)
        for (int i = 1; i <= -expo; i++)
            res = res / 10.0;
    return res;
}

string number::to_string() {

}

number operator+ (number &a, number &b) {
    
}

number operator- (number &a, number &b) {

}

number operator* (number &a, number &b) {

}

number operator/ (number &a, number &b) {

}

number operator% (number &a, number &b) {

}
number operator^ (number &a, number &b) {

}
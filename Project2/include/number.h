#include <string>
const int PRECISION = 100;

using std::string;

struct number {
    int digits[PRECISION * 2];
    int expo = -1, length;
    bool is_negtive = false;

    long double to_longdouble();
    double to_double();
    string to_string();
    void print();

    number (string str);
    number (long double lf);
    number ();
};

number operator+ (number &a, number &b);
number operator- (number &a, number &b);
number operator* (number &a, number &b);
number operator/ (number &a, number &b);
number operator% (number &a, number &b);
number operator^ (number &a, number &b);
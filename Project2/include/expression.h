#include <cstring>
#include "number.h"

using std::string;

struct expression {
    number *value = nullptr;
    string str;
};

expression operator+ (expression &a, expression &b);
expression operator- (expression &a, expression &b);
expression operator* (expression &a, expression &b);
expression operator/ (expression &a, expression &b);
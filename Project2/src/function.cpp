// to be implemented high precision...

#include <cmath>
#include <functional>
#include <map>
#include <cstring>
using std::map;
using std::function;

map<string, function<number(number)>> functions;

number sin_f(number x) {
    return number(std::sin(x.to_longdouble()));
}

number cos_f(number x) {
    return number(std::cos(x.to_longdouble()));
}

number arctan_f(number x) {
    return number(std::atan(x.to_longdouble()));
}

number ln_f(number x) {
    return number(std::log10(x.to_longdouble()));
}

number exp_f(number x) {
    return number(std::exp(x.to_longdouble()));
}

number sqrt_f(number x) {
    return number(std::sqrt(x.to_longdouble()));
}

map<string, function<number(number)>> get_functions() {
    functions["sin"] = sin_f;
    functions["cos"] = cos_f;
    functions["arctan"] = arctan_f;
    functions["ln"] = ln_f;
    functions["exp"] = exp_f;
    functions["sqrt"] = sqrt_f;
    return functions;
}
#include <map>
#include <functional>

using std::map;
using std::function;

number sin_f(number x);
number cos_f(number x);
number arctan_f(number x);
number ln_f(number x);
number exp_f(number x);
number sqrt_f(number x);

map<string, function<number(number)>> get_functions();


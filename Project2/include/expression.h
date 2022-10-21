#include <cstring>
#include "number.h"

using std::string;

struct expression {
    number *value = nullptr;
    string str;
};
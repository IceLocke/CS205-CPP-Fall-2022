#include <map>
#include <stack>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <functional>
#include "expression.h"

using std::isdigit;
using std::function;
using std::string;
using std::vector;
using std::stack;
using std::cerr;
using std::endl;
using std::map;

struct ExpressionPhaser {
    enum StringType {
        NUMBER = 0, 
        VARIABLE = 1, 
        FUNCTION = 2, 
        OPERATOR = 3
    };

    enum OperatorPriority {
        NOT_OPERATOR = 0,
        LOW = 1,
        MEDIUM = 2,
        HIGH = 3
    };

    stack<string> operators;
    stack<number> nums;
    vector<string> strings;
    vector<StringType> string_types;
    map<string, expression> &var;
    map<string, function<number(number)>> &functions;

    void divide_string(expression e);
    bool is_equation(expression e);
    void calculate_top(bool is_function);
    OperatorPriority operator_priority(char ch);
    number caculate_expression(expression e, map<string, expression> &variables);
};
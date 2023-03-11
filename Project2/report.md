# CS205 2022 Fall Project 2 Report

本项目使用 GitHub 进行代码管理，项目地址：[https://github.com/IceLocke/2022-Fall-CPP-Project2](https://github.com/IceLocke/2022-Fall-CPP-Project2)

## Part 1 - Analysis
对于本次的计算器project，由于功能实现较为复杂，采用了面向对象的设计方法，设计了以下类：

Class | Description
---|---
Expression|存储表达式，及表达式的值
Number|高精度数字类，支持四则运算以及取模和乘方运算
ExpressionPhaser|存储预先定义的函数、自变量的值，并且对表达式进行解析计算

同时，对于功能我将该project分成两个主要模块：
1. 字符串表达式解析
2. 高精度计算

接下来我分别对其进行分析和介绍。

### 字符串表达式解析
原本打算使用递归的方式处理带括号的表达式，但发现递归的方式运行效率较低，于是采用维护两个栈（分别存储运算符、变量或数字）的方式来进行从左往右的带优先级的表达式解析。

为了处理方便，对于一个字符串，我们将其分类拆分：
1. 数字
2. 单词（可能为函数名或者变量名）
3. 运算符 & 括号

例如，`(sin(3*x)+3.14)*7` 们将其拆分为`( sin ( 3 * x ) + 3.14 ) * 7`，然后从左往右扫描拆分后的字符串，按照以下规则进行处理：
1. 如果拆分后的字符串为运算符，判断其优先级（后附优先级参考表），按照从强到弱的优先级顺序，将栈顶比自己优先级高的运算符号进行依次处理，从数字变量栈顶取两个（也需要特判是否是负数的'-'运算符）数字进行运算，运算后重新压入数字栈中。最后将读取到的运算符压入栈中。
2. 如果拆分后的字符串为`'('`，直接压入运算符栈中。
3. 如果拆分后的字符串为`')'`，将栈顶的运算符号依次弹出进行计算直到将最近匹配的左括号弹出。最后进行一次数学函数括号的判断，然后将计算后的结果，结合使用`std::function`存储的函数（如果需要的话），压入数字栈中。
4. 如果拆分后的字符串为变量或者数字，转换后（如果需要的话），压入数字栈中。

最后，如果运算符栈未空，将栈顶元素弹出依次计算，最后取数字栈中的结果作为表达式的计算结果。

#### 解析器实现细节等
##### 运算级优先表
用函数 `operator_priority() `和枚举类 `OperatorPriority` 实现。
Priority | Operators
---|---
HIGH|^
MEDIUM|*, /, %
LOW|+, -
##### 函数表
由于时间有限，并未将其实现高精度，由于代码存在一定可扩展性，后续实现高精度除法之后可以考虑采用牛顿迭代或者泰勒展开实现相关函数。
Function|Description
---|---
sqrt(x)|x的算数平方根
sin(x)|x在弧度制下的正弦值
cos(x)|x在弧度制下的余弦值
arctan(x)|x的反正切函数
ln(x)|自然对数
exp(x)|以e为底的指数函数


### 高精度运算
考虑到可扩展性，我实现了一个高精度运算（+，*）的高精度类，支持200位有效数字。由于除法、取模和乘方实现较为复杂（考虑到小数乘方），故我考虑将部分有效数字转化为 `long double`，然后使用 `cmath` 的函数直接进行计算，然后再将计算结果转换为高精度类。

#### 高精度加法
模拟竖式运算即可，将大于10的数字位前移，顺序相加完成运算。需要注意的细节是，由于高精度类存在有效数字以及10的指数部分，需要将最低位精确位数较低的数字进行padding处理，其中小数点偏移的问题较为麻烦，编写代码的时候需要注意。

#### 高精度乘法
由于有效数字只有200位，故不考虑采取project1中的fft的方法实现高精度乘法，仅使用模拟竖式运算的方法。只需要将有效位数全部相乘，然后将10的指数部分相加即可。

## Part 2 - Code
**仅包含部分关键代码**

### 表达式解析器
```cpp
// expression_phaser.cpp
// Code Reference: https://blog.csdn.net/qq_45768060/article/details/105414612

// 计算栈顶的函数，并且进行 (-112) 这样的附属表达式的特判。
// 使用运算符表的方式进行编写，具有一定的拓展性。
void ExpressionPhaser::calculate_top(bool is_function) {
    if (is_function) {
        function<number(number)> func = (*functions)[operators.top()];
        number top_num = nums.top();
        nums.pop();
        nums.push(func(top_num));
        operators.pop();
        return;
    }

    // from left to right, get numbers from up to down
    char op = operators.top()[0];
    operators.pop();

    // check whether is a negtive number, or wrong expression
    if (nums.size() == 1) {
        if (op == '+' || op == '-') {
                if (op == '+')
                    return;
                else {
                    number top_num = nums.top();
                    top_num.is_negtive = !top_num.is_negtive;
                    nums.pop();
                    nums.push(top_num);
                }
            }
        else {
            cerr << "Wromg expression!";
        }
        return;
    }

    number b = nums.top();
    nums.pop();
    number a = nums.top();
    nums.pop();
    switch (op) { 
        case '+': nums.push(a + b); break;
        case '-': nums.push(a - b); break;
        case '*': nums.push(a * b); break;
        case '/': nums.push(a / b); break;
        case '%': nums.push(a % b); break;
        case '^': nums.push(a ^ b); break;
        default:
            cerr << "Unkown operator!" << endl;
            break;
    }
}

// 字符串分割，原本考虑使用正则表达式进行解析，后面本着造轮子的态度自己写了一遍
void ExpressionPhaser::divide_string(expression e) {

    string &str = e.str;
    string num, word;
    bool is_variable = false;
    strings.clear();
    string_types.clear();

    int len = str.length(), i = 0;
    while (i < len) {
        if (isspace(str[i])) {
            i++;
            continue;
        }
        if (isdigit(str[i]) || str[i] == '.') {
            num.push_back(str[i]);
        }
        else {
            if (num.length()) {
                strings.push_back(num);
                string_types.push_back(NUMBER);
                num.erase();
            }
            // funtion name or variable name
            if (isalpha(str[i]))
                word.push_back(str[i]);
            else {
                if (word.length()) {
                    strings.push_back(word);
                    if (var->count(word))
                        string_types.push_back(VARIABLE);
                    else if (is_function(word))
                        string_types.push_back(FUNCTION);
                    else {
                        cerr << word << ": Undefined function or variable!" << endl;
                        return;
                    }
                    word.erase();
                }
                if (is_operator(str[i])) {
                    strings.push_back(str.substr(i, 1));
                    string_types.push_back(OPERATOR);
                }
                else {
                    if (!isspace(str[i]))
                        cerr << "Expression have undefined character!" << endl;
                }
            }
        }
        i++;
    }
    if (num.length()) strings.push_back(num);
    if (word.length()) strings.push_back(word);
}

// 计算表达式，主要负责进行运算符优先级的逻辑处理
number ExpressionPhaser::calculate_expression(expression e) {
    divide_string(e);
    int strings_size = strings.size();
    for (int i = 0; i < strings_size; i++) {
        if (string_types[i] == OPERATOR || string_types[i] == FUNCTION) {
            // pass low priority operators, deal with medium priority
            if (operator_priority(strings[i][0]) == LOW) { 
                while (!operators.empty()) {
                    if (operators.top()[0] == '(')
                        break;
                    calculate_top(false);
                }
                operators.push(strings[i]);
            }
            // deal with operators with higher priority
            else if (operator_priority(strings[i][0]) == MEDIUM) {
                while (!operators.empty()) {
                    if (operator_priority(operators.top()[0]) != MEDIUM)
                        break;
                    calculate_top(false);
                }
                operators.push(strings[i]);
            }
            else if (operator_priority(strings[i][0]) == HIGH)
                operators.push(strings[i]);
            else if (strings[i][0] == '(')
                operators.push(strings[i]);
            else if (strings[i][0] == ')') {
                while (operators.top() != "(")
                    calculate_top(false);
                operators.pop();
                if (!operators.empty())
                    if (is_function(operators.top()))
                        calculate_top(true);
            }
            else if (is_function(strings[i]))
                operators.push(strings[i]);
        }
        else {
            number num;
            if (var->count(strings[i]))
                num = (*var)[strings[i]];
            else
                num = number(strings[i]);
            nums.push(num);
        }
    }
    while (!operators.empty())
        calculate_top(false);
    
    number res = nums.top();
    nums.pop();
    
    while(!operators.empty()) operators.pop();
    while(!nums.empty()) nums.pop();

    return res;
}
```
### 大数字计算
```cpp
// number.h
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

// number.cpp
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
```

### 主函数
```cpp
// main.cpp
int main() {
    cout << WELCOME_TEXT;
    string user_input;

    // init part
    expression e;
    number res;
    map<string, number> var;
    
    map<string, function<number(number)>> functions = get_functions();
    ExpressionPhaser *phaser = new ExpressionPhaser(&var, &functions);

    while (true) {
        cin >> e.str;
        if (e.str != "quit") {
            if (phaser->is_equation(e)) {
                int pos;
                for (pos = 0; pos < e.str.length(); pos++)
                    if (e.str[pos] == '=')
                        break;
                if (pos != 0) {
                    var[e.str.substr(0, pos)] = number(e.str.substr(2, e.str.length()-1));
                }
                else cerr << "No variable name!";               
            }
            else {
                res = phaser->calculate_expression(e);
                cout << res.to_string() << endl;
            }
        }
        else break;
    }

    free(phaser);

    return 0;
}
```
## Part 3 - Result & Verification
### Test Case 1 - Basic Calculations
```
----------
 Simple caculator v1.0 
 Copyright Gong Linghu 
 Tip: Enter 'quit' (without quote) to end the program. 
---------
2+3
5
5+2*3
11
(5+2)*3
21
```
### Test Case 2 - Variables and Functions
```
----------
 Simple caculator v1.0 
 Copyright Gong Linghu 
 Tip: Enter 'quit' (without quote) to end the program. 
---------
x=3
y=6
x+2*y
15
sqrt(x+y)*3
9
arctan(sqrt(3))
1.047198
sin(sqrt(2)/2)+1
1.649637
```
### Test Case 3 - High Precision Cacultaions
```
----------
 Simple caculator v1.0 
 Copyright Gong Linghu 
 Tip: Enter 'quit' (without quote) to end the program. 
---------
1.723812783*1.2222+0.0000000000001
2.1068439833827
0.0000000000001+99999999999.6666666
99999999999.6666666000001
718237821738*671267
482129347884602046
```
### Test Case 4 - Error Detection
```
----------
 Simple caculator v1.0 
 Copyright Gong Linghu 
 Tip: Enter 'quit' (without quote) to end the program. 
---------
notafuntion(3)
notafuntion: Undefined function or variable!
notafuntion
x+1
x: Undefined function or variable!
x
```

### Test Case 5 - Others
```
----------
 Simple caculator v1.0 
 Copyright Gong Linghu 
 Tip: Enter 'quit' (without quote) to end the program. 
---------
217837128.322^22.33+3*11+10.333)*8912+sin(3.1415926)
13818489610523457952516646775506534821465318136106901964562456791213233104316043451849793347461767300110090887564639419143607338908619368959446106486369436500306889027039804437388780267496583.696
1+2%2*10+3
4
```

## Part 4 - Difficulties & Solutions
### 高精度加法小数点对齐
考虑采用 padding 的方式进行处理：
```
// add by padding
//  7654321.012
//   000076.54321123
```
根据 number 的 expo 和 length 判断小数精确位数即可。

### 其他高精度运算
虽然说不算是严格的 Solution，对于较难实现的运算，以及数学函数复合，转化为浮点数后使用 STL 内建函数进行处理。

### 字符串解析
我认为这是这个 Project 最难的部分之一，相当于在写编译器的表达式解析功能。由于中缀表达式仅易于人类阅读，而机器编写后缀表达式或者前缀表达式解析更为方便，主要有两种解决办法：
1. 将中缀表达式转化为后缀表达式
2. 直接通过栈计算

由于第二种方式较为直观，编写起来也不算特别困难，我就采取了这种方法。具体的实现方法可以参照 Analysis 部分。

### 函数和变量映射
考虑使用 STL 的 Hashmap 进行从字符串到 number 类型或者 std::function 类型的映射，这样的拓展性较强，且容易进行面向对象的编写。

### Part 5 - Todos

1. 更加完善的表达式错误纠正机制。目前仅检查是是否有运算符错误或者变量/函数名错误。
2. 完善高精度除法、取模运算，采取无精度损失的算法。
3. 多元数学函数的支持。
4. 更友好的用户交互。
5. 自定义函数、变量自增自减运算等。

这些都是初期设想时有打算完成的，但由于时间有限，以及(对自己好一点.jpg)于是没有完成。
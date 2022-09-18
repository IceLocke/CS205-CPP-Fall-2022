#include <iostream>
// A小写，add.cpp
#include "add.cpp"
// 命名空间
using namespace std;
int main() {
    // 全角空格, 
    int num1 = 2147483647;
    int num2 = 1;
    long long result = 0;
    // 全角分号
    result = add(num1, num2);
    // 全角引号
    // 2147483647 + 1 溢出
    cout << "The result is " << result << endl;
    return 0;
}
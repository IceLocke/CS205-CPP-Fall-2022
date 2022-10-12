#include <iostream>
#include <cstdio>
#include "stuinfo.hpp"

const int LEN = 5;

stuinfo stu[LEN];

using std::cin;
using std::cout;

int main() {
    inputstu(stu, LEN);
    showstu(stu, LEN);
    sort(stu, LEN);
    
    char ch[20];
    cout << "Please input the name you want to find: ";
    cin.getline(ch, 20);
    if (findstu(stu, LEN, ch))
        printf("%s is in the students list.\n", ch);
    else
        printf("%s is not in the students list.\n", ch);

}
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include "stuinfo.hpp"

using std::cout; 
using std::endl;
using std::cin;

bool cmp(stuinfo a, stuinfo b) {
    return a.ave < b.ave;
}

void inputstu(stuinfo stu[], int n) {
    cout << "Please input information of " << n << " students:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Student " << i << "'s name:";
        cin.getline(stu[i].name, 20);
        cout << "Student " << i << "'s scores:";
        for (int j = 0; j < 3; j++)
            cin >> stu[i].score[j];
        getchar();
        stu[i].ave = ((double)(stu[i].score[0] + stu[i].score[1] + stu[i].score[2])) / 3.00;
    }
}

void showstu(stuinfo stu[], int n) {
    cout << "The infomation of " << n << " students you input:" << endl;
    for (int i = 0; i < n; i++) {
        printf("Student %d name: %s, scores: %.0lf %.0lf %.0lf\n", 
                i, stu[i].name, stu[i].score[0], stu[i].score[1], stu[i].score[2]);
    }
}

void sort(stuinfo stu[], int n) {
    std::sort(stu, stu + n, cmp);
    printf("The descending order of the students:\n");
    for (int i = 0; i < n; i++) {
        printf("Student %d name: %s, scores: %.0lf %.0lf %.0lf average: %lf\n", 
                i, stu[i].name, stu[i].score[0], stu[i].score[1], stu[i].score[2], stu[i].ave);
    }
}

bool findstu(stuinfo stu[], int n, char ch[]) {
    int len = strlen(ch);
    for (int i = 0; i < n; i++) {
        bool ok = true;
        for (int j = 0; j < len; j++)
            if (ch[j] != stu[i].name[j]) {
                ok = false;
                break;
            }
        if (ok) return true;
    }
    return false;
}
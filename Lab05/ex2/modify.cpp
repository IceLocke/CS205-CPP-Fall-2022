#include <iostream>
using namespace std;

int main() {
    char *p = new char[11];
    *(p + 10) = '\0';
    for (char *i = p; i < p + 10; i++)
        *i = (int)(i - p) + 'A';
    cout << p << endl;
    *(p + 11) = 'A';
    cout << char(*(p + 11)) << endl;
    return 0;
}
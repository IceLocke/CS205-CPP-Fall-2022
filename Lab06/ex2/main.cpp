#include <iostream>
#include <cstring>

using std::cout;
using std::cin;
using std::endl;

char* match(char *s, char ch);

int main() {
    char str[1000], ch;
    
    cout << "Please input a string:" << endl;
    cin.getline(str, 1000);
    cout << "Please input a character:" << endl;
    cin >> ch;

    char *start = match(str, ch);
    if (start != NULL)
        while (*start != '\0')
            cout << *start++;
    else
        cout << "Not Found";
    cout << endl;
    
    return 0;
}

char *match(char *s, char ch) {
    int len = strlen(s);
    for (int i = 0; i < len; i++)
        if (s[i] == ch)
            return s + i;
    return NULL;
}
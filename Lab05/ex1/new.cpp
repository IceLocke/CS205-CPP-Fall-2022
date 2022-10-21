#include <iostream>
using namespace std;

int main() {
    int *a = new int[5]{1, 2, 3, 4, 5};
    for (int *i = a + 4; i >= a; i--)
        cout << *i << " ";
    cout << endl;
    free(a);
    return 0;
}
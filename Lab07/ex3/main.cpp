#include <iostream>

using std::cout;
using std::endl;

template <typename T>
T minimum(T &a, T &b) {
    return a < b ? a : b;
}

int main() {

    int a = 1, b = 0;
    char c = 'A', d = 'F';
    float e = -1.1f, f = 2.0f;

    cout << minimum(a, b) << endl << minimum(c, d) << endl << minimum(e, f) << endl;

}

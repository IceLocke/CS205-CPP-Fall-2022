#include <iostream>
#include <cmath>

using std::cout;
using std::endl;

int vabs(int *p, size_t n) {
    int res = 0;
    while (n--) {
        res += (*p) > 0 ? *p : -*p;
        p++;
    }
    return res;
}

float vabs(float *p, size_t n) {
    float res = 0.0f;
    while (n--) {
        res += (*p) > 0.0f ? *p : -*p;
        p++;
    }
    return res;
}

double vabs(double *p, size_t n) {
    double res = 0.0;
    while (n--) {
        res += (*p) > 0.0 ? *p : -*p;
        p++; 
    }
    return res;
}

int main() {

    int a[] = {1, -1, 2, -2};
    float b[] = {1.1f, -1.1f, 2.2f, -2.2f};
    double c[] = {1.1, -1.1, 2.2, -2.2};

    cout << vabs(a, 4) << endl << vabs(b, 4) << endl << vabs(c, 4) << endl;

    return 0;
}
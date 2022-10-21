#include "libswap.h"

void int_swap(int a, int b) {
    int t = a;
    a = b;
    b = t;
}

void ptr_swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void ref_swap(int &a, int &b) {
    int t = a;
    a = b;
    b = t;
}
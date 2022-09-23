__int128 fac(int n) {
    __int128 res = n;
    for (int i = n - 1; i >= 2; i--)
        res = res * i;
    return res;
}
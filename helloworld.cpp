#include <iostream>
#include <string.h>
#include <cstring>
using namespace std;
using std::to_string;
int main() {
   long double d = 0.0000021316934;
   string s = to_string(d);
   cout << "Conversion of double to string: " << s;
   return 0;
}
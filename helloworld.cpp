#include <iostream>
using namespace std;

int main() {
int * pint = (int*) malloc(8*sizeof(int));

char * pc = (char*) pint;

pc[8]='a';

*(pc+8)='b';

}
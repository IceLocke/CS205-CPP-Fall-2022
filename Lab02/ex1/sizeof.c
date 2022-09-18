#include <stdio.h>
#include <stdbool.h>
int main() {
    printf("\nPrint size of the fundamental types:\n");
    printf("-----------------------------------------\n");
    printf("The sizeof(char) is: %d bytes.\n", sizeof(char));
    printf("The sizeof(short) is: %d bytes.\n", sizeof(short));
    printf("The sizeof(int) is: %d bytes.\n", sizeof(int));
    printf("The sizeof(long) is: %d bytes.\n", sizeof(long));
    printf("The sizeof(long long) is: %d bytes.\n", sizeof(long long));
    printf("The sizeof(float) is: %d bytes.\n", sizeof(float));
    printf("The sizeof(double) is: %d bytes.\n", sizeof(double));
    printf("The sizeof(long double) is: %d bytes.\n", sizeof(long double));
    printf("The sizeof(bool) is: %d byte.\n", sizeof(bool));
    return 0;
}

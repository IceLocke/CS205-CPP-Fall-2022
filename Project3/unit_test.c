#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrix.h"

void printMatrix(struct Matrix* m) {
    if (m != NULL) {
        if (m->pData != NULL) {
            size_t i, j;
            for (i = 0; i < m->row; i++) {
                for (j = 0; j < m->col; j++)
                    printf("%f ", m->pData[i * m->col + j]);
                printf("\n");
            }
            printf("\n");
        }
    }
}

void matrixAllocationTest();
void matrixElementsAccessingTest();
void matrixInitializingTest();
void matrixCopyingTest();
void matrixOpertaionTest();
void matrixPropertiesTest();
void matrixBasicOperaionsTest();
void safetyTest();

int main() {

    matrixAllocationTest();
    matrixElementsAccessingTest();
    matrixInitializingTest();
    matrixCopyingTest();
    matrixOpertaionTest();
    matrixPropertiesTest();
    matrixBasicOperaionsTest();
    safetyTest();

    return 0;
}

void matrixAllocationTest() {
    printf("### Allocation Test\n");
    struct Matrix *m = createMatrix(4, 4);
    matrixSetAllZero(m);
    printMatrix(m);
    safeDeleteMatrix(m, &m);
    safeDeleteMatrix(m, &m);
    deleteMatrix(m);
    printf("###\n");
}

void matrixElementsAccessingTest() {
    printf("### Element Accessing Test\n");
    struct Matrix *m = createMatrix(4, 4);
    matrixSetIdentity(m);
    size_t i, j;
    for (i = 1; i <= m->row; i++) {
        for (j = 1; j <= m->col; j++)
            printf("%f ", matrixGetElement(m, i, j));
        printf("\n");
    }
    matrixSetElement(m, 3, 3, 5.0f);
    for (i = 1; i <= m->row; i++) {
        for (j = 1; j <= m->col; j++)
            printf("%f ", matrixGetElement(m, i, j));
        printf("\n");
    }
    printf("%p %p\n", m->pData, matrixGetPData(m));
    safeDeleteMatrix(m, &m);
    printf("###\n");
}

void matrixInitializingTest() {
    printf("### Initialzing Test\n");
    struct Matrix *m1 = createMatrix(4, 4);
    struct Matrix *m2 = createMatrix(5, 4);
    matrixSetAll(m1, 1.0);
    printMatrix(m1);
    matrixSetAllZero(m1);
    printMatrix(m1);
    matrixSetAllZero(m2);
    matrixSetIdentity(m1);
    matrixSetIdentity(m2);
    printMatrix(m1);
    printMatrix(m2);
    safeDeleteMatrix(m1, &m1);
    safeDeleteMatrix(m2, &m2);
    printf("###\n");
}

void matrixCopyingTest() {
    printf("### Matrix Copying Test\n");
    struct Matrix *m1 = createMatrix(4, 4);
    struct Matrix *m2 = createMatrix(4, 5);
    matrixSetIdentity(m1);
    copyMatrix(m2, m1);
    printMatrix(m2);
    struct Matrix *m3 = NULL;
    safeCopyMatrix(m3, &m3, m1);
    printMatrix(m3);
    swapMatrix(m1, m2);
    printMatrix(m1);
    printMatrix(m2);
    safeDeleteMatrix(m1, &m1);
    safeDeleteMatrix(m2, &m2);
    safeDeleteMatrix(m3, &m3);
    printf("###\n");
}   

void matrixOpertaionTest() {
    printf("### Matrix Operation Test\n");
    struct Matrix *m1 = createMatrix(4, 4);
    struct Matrix *m2 = createMatrix(4, 4);
    struct Matrix *m3 = createMatrix(4, 4);

    matrixSetAll(m1, 1.0f);
    matrixSetIdentity(m2);
    copyMatrix(m3, m1);

    printMatrix(m1);
    printMatrix(m2);

    addMatrix(m1, m2);
    printMatrix(m1);

    copyMatrix(m1, m3);
    subtractMatrix(m1, m3);
    printMatrix(m1);

    copyMatrix(m1, m3);
    multiplyMatrix(m1, m2);
    printMatrix(m1);

    copyMatrix(m1, m3);
    addScalarToMatrix(m1, 5.0f);
    printMatrix(m1);

    subtractScalarFromMatrix(m1, 5.0f);
    printMatrix(m1);

    matrixMultiplyScalar(m1, 10.0f);
    printMatrix(m1);

    matrixSetAllZero(m1);
    matrixSetAllZero(m2);
    printf("m1 and m2 are equal: %d\n", matrixIsEqual(m1, m2));

    safeDeleteMatrix(m1, &m1);
    safeDeleteMatrix(m2, &m2);
    safeDeleteMatrix(m3, &m3);
    printf("###\n");
}

void matrixPropertiesTest() {
    printf("### Matrix Properties Test\n");
    time_t t;
    srand((unsigned) time(&t));
    struct Matrix *m = createMatrix(4, 4);
    
    int i, j;
    for (i = 1; i <= m->row; i++) {
        for (j = 1; j <= m->col; j++)
            matrixSetElement(m, i, j, (float)(rand() % 10));
    }

    printMatrix(m);

    size_t row, col;
    printf("%f\n", matrixMax(m));
    matrixMaxIndex(m, &row, &col);
    printf("%lu %lu\n", row, col);

    printf("%f\n", matrixMin(m));
    matrixMinIndex(m, &row, &col);
    printf("%lu %lu\n", row, col);

    safeDeleteMatrix(m, &m);
    printf("###\n");
}

void matrixBasicOperaionsTest() {
    printf("### Matrix Basic Operation Test\n");
    time_t t;
    srand((unsigned) time(&t));
    struct Matrix *m = createMatrix(4, 4);
    
    int i, j;
    for (i = 1; i <= m->row; i++) {
        for (j = 1; j <= m->col; j++)
            matrixSetElement(m, i, j, (float)(rand() % 10));
    }

    printMatrix(m);

    matrixSwapRow(m, 1, 2);
    printMatrix(m);

    matrixSwapColumn(m, 1, 2);
    printMatrix(m);

    matrixAddRow(m, 1, 2, 1);
    printMatrix(m);

    matrixAddColumn(m, 1, 2, 1);
    printMatrix(m);

    matrixRowMultiplyScalar(m, 4, 2);
    printMatrix(m);

    matrixColMultiplyScalar(m, 4, 2);
    printMatrix(m);
    
    safeDeleteMatrix(m, &m);
    printf("###\n");
}

void safetyTest() {
    printf("### Matrix Safety Operation Test");
    struct Matrix *m = createMatrix(4, 4);
    matrixSetAllZero(m);
    deleteMatrix(m);
    safeMatrixGetElement(m, 1, 1);
    safeMatrixSetElement(m, 1, 1, 1.0f);
    printf("###\n");
}

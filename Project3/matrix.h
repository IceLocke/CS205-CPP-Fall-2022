#ifndef __MATRIX_H__
#define __MATRIX_H__
struct Matrix {
    int row, col;
    float *pData;
};

Matrix* createMatrix(int row, int col);
void copyMatrix(Matrix *fromMatrix, Matrix *toMatirx);
Matrix* addMatrix(const Matrix *a, const Matrix *b);


#endif
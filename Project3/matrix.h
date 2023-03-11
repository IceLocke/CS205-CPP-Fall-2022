#ifndef __MATRIX_H__
#define __MATRIX_H__
#include <stdlib.h>
#include <string.h>

struct Matrix {
    size_t row, col;
    float *pData;
};

struct MatrixNode {
    struct Matrix *matrix;
    struct MatrixNode *left;
    struct MatrixNode *right; 
};

/*
    Matrix pointer management
    DON'T USE THESE FUNCTIONS MANUALLY!!
*/
void addMatrixPtr(struct Matrix *const m);
void deleteMatrixPtr(const struct Matrix *const m);
int matrixPtrExist(const struct Matrix *const m);

/*
    Matrix allocation
*/

/// @brief Create a new matrix with specific rows and columns.
/// @param row Number of rows of new matrix
/// @param col Number of columns of new matrix
/// @return Pointer of the new matrix, if didn't create successfully, return NULL.
struct Matrix* createMatrix(const size_t row, const size_t col);

/// @brief Delete an existed matirx, with its inner data.
/// @param targetMatrix Pointer of the matrix to delete
/// @return 0 if successfully deleted, otherwise 1.
int deleteMatrix(struct Matrix *const targetMatrix);

/// @brief Delete an existed matirx, with its inner data, with existence check.
/// @param targetMatrix Pointer of the matrix to delete
/// @param targetMatrixP Pointer of pointer of the matrix to delete
/// @return 0 if successfully deleted, otherwise 1.
int safeDeleteMatrix(struct Matrix *const targetMatrix, 
                     struct Matrix **targetP);

/*
    Matrix elements accessing
*/

/// @brief Get an element of a matrix by the index i, j.
/// @param srcMatrix Pointer of the matrix to access
/// @param i Index of the row
/// @param j Index of the column
/// @return The value of the element, if the element cannot be access it will be permanently zero.
float matrixGetElement(const struct Matrix *const srcMatrix, 
                       const size_t i, const size_t j);

/// @brief Get an element of a matrix by the index i, j, with existence check.
/// @param srcMatrix Pointer of the matrix to access
/// @param i Index of the row
/// @param j Index of the column
/// @return The value of the element, if the element cannot be access it will be permanently zero.
float safeMatrixGetElement(const struct Matrix *const srcMatrix, 
                           const size_t i, const size_t j);

/// @brief Set an element of a matrix by the index i, j.
/// @param targetMatrix Pointer of the matrix to set
/// @param i Index of the row
/// @param j Index of the column
/// @param value Value that you wants to set
/// @return 0 if successfully set, otherwise 1.
int matrixSetElement(struct Matrix *const targetMatrix, 
                     const size_t i, const size_t j, const float value);
/// @brief Get an element of a matrix by the index i, j, with existence check.
/// @param srcMatrix Pointer of the matrix to access
/// @param i Index of the row
/// @param j Index of the column
/// @return The value of the element, if the element cannot be access it will be permanently zero.
int safeMatrixSetElement(struct Matrix *const targetMatrix, 
                         const size_t i, const size_t j, const float value);

/// @brief Get pointer of pData of a matrix.
/// @param srcMatrix Pointer of the matrix to access
/// @return Pointer of pData of a matrix. If it doesn't exits, return NULL.
float* matrixGetPData(const struct Matrix *const srcMatrix);

/// @brief Get pointer of pData of a matrix, with existence check.
/// @param srcMatrix Pointer of the matrix to access
/// @return Pointer of pData of a matrix. If it doesn't exits, return NULL.
float* safeMatrixGetPData(const struct Matrix *const srcMatrix);

/*
    Initializing matrix
*/

/// @brief Set the elements of a matrix to a same certain value.
/// @param targetMatrix Pointer of the matrix to set
/// @param value Value to set the elements
/// @return 0 if successfully set, otherwise 1.
int matrixSetAll(struct Matrix *const targetMatrix, 
                 float value);

/// @brief Set the elements of a matrix to a same certain value, with existence check.
/// @param targetMatrix Pointer of the matrix to set
/// @param value Value to set the elements
/// @return 0 if successfully set, otherwise 1.
int safeMatrixSetAll(struct Matrix *const targetMatrix, 
                     float value);

/// @brief Set the elements of a matrix to zero.
/// @param targetMatrix Pointer of the matrix to set
/// @return 0 if successfully set, otherwise 1.
int matrixSetAllZero(struct Matrix *const targetMatrix);

/// @brief Set the elements of a matrix to zero, with existence check.
/// @param targetMatrix Pointer of the matrix to set
/// @return 0 if successfully set, otherwise 1.
int safeMatrixSetAllZero(struct Matrix *const targetMatrix);

/// @brief Set a matrix to an identidy matrix, remain the same size.
/// @param targetMatrix Pointer of the matrix to set
/// @return 0 if successfully set, otherwise 1.
int matrixSetIdentity(struct Matrix *const targetMatrix);

/// @brief Set a matrix to an identidy matrix, remain the same size, with existence check.
/// @param targetMatrix Pointer of the matrix to set
/// @return 0 if successfully set, otherwise 1.
int safeMatrixSetIdentity(struct Matrix *const targetMatrix);

/*
    Copying matrix
*/

/// @brief Copy a matrix to an another matrix.
/// @param targetMatrix Pointer of the matrix copying to
/// @param srcMatrix Pointer of the matrix copying from
/// @return 0 if successfully copied, otherwise 1.
int copyMatrix(struct Matrix *const targetMatrix, 
               const struct Matrix *const srcMatrix);

/// @brief Copy a matrix to an another matrix, with existence check. \n
/// @brief If the targetMatrix is not exist, the function will automatically create one.
/// @param targetMatrix Pointer of the matrix copying to
/// @param targetMatrixP Pointer of pointer of the matrix copying to
/// @param srcMatrix Pointer of the matrix copying from
/// @return 0 if successfully copied, otherwise 1.
int safeCopyMatrix(struct Matrix *const targetMatrix,
                   struct Matrix **const targetMatrixP,
                   const struct Matrix *const srcMatrix);

/// @brief Swap the content of two matrix.
/// @param a Pointer of pointer of one matrix
/// @param b Pointer of pointer of another one matrix
/// @return 0 if successfully copied, otherwise 1.
int swapMatrix(struct Matrix *const a, struct Matrix *const b);
               
/// @brief Swap the content of two matrix, with existence check.
/// @param a Pointer of pointer of one matrix
/// @param b Pointer of pointer of another one matrix
/// @return 0 if successfully copied, otherwise 1.
int safeSwapMatrix(struct Matrix *const a, struct Matrix *const b);

/*
    Matrix operations
*/

/// @brief Add two matrix with the same size,
/// @brief result will be stored in a, and b remains the same.
/// @param a Pointer of one matrix
/// @param b Pointer of another one matrix
/// @return 0 if successfully added, otherwise 1. 
int addMatrix(struct Matrix *const a, const struct Matrix *const b);

/// @brief Add two matrix with the same size with existence check,
/// @brief result will be stored in a, and b remains the same.
/// @param a Pointer of one matrix
/// @param b Pointer of another one matrix
/// @return 0 if successfully added, otherwise 1. 
int safeAddMatrix(struct Matrix *const a, const struct Matrix *const b);

/// @brief Subtract two matrix with the same size,
/// @brief result will be stored in a, and b remains the same.
/// @param a Pointer of one matrix
/// @param b Pointer of another one matrix
/// @return 0 if successfully copied, otherwise 1. 
int subtractMatrix(struct Matrix *const a, const struct Matrix *const b);

/// @brief Subtract two matrix with the same size with existence check,
/// @brief result will be stored in a, and b remains the same.
/// @param a Pointer of one matrix
/// @param b Pointer of another one matrix
/// @return 0 if successfully copied, otherwise 1. 
int safeSubtractMatrix(struct Matrix *const a, const struct Matrix *const b);

/// @brief Multiply two matrix if they can be multiplied,
/// @brief result will be stroed in a, and b remains the same.
/// @param a Poiner of one matrix
/// @param b Pointer of another one matrix
/// @return 0 if successfully copied, otherwise 1.
int multiplyMatrix(struct Matrix *const a, const struct Matrix *const b);

/// @brief Multiply two matrix if they can be multiplied, also checking the existence,
/// @brief result will be stroed in a, and b remains the same.
/// @param a Poiner of one matrix
/// @param b Pointer of another one matrix
/// @return 0 if successfully copied, otherwise 1.
int safeMultiplyMatrix(struct Matrix *const a, const struct Matrix *const b);

/// @brief Add a scalar to all the elements of the matrix.
/// @param targetMatrix Pointer of the matrix adding scalar to
/// @param scalar The adding value
/// @return 0 if successfully copied, otherwise 1.
int addScalarToMatrix(struct Matrix *const targetMatrix, float scalar);

/// @brief Add a scalar to all the elements of the matrix, with existence check.
/// @param targetMatrix Pointer of the matrix adding scalar to
/// @param scalar The adding value
/// @return 0 if successfully copied, otherwise 1.
int safeAddScalarToMatrix(struct Matrix *const targetMatrix, float scalar);

/// @brief Subtract a scalar from all the elements of the matrix.
/// @param targetMatrix Pointer of the matrix subtracting scalar from
/// @param scalar The subtracting value
/// @return 0 if successfully copied, otherwise 1.
int subtractScalarFromMatrix(struct Matrix *const targetMatrix, 
                             float scalar);

/// @brief Subtract a scalar from all the elements of the matrix, with existence check.
/// @param targetMatrix Pointer of the matrix subtractig scalar from
/// @param scalar The subtracting value
/// @return 0 if successfully copied, otherwise 1.
int safeSubtractScalarFromMatrix(struct Matrix *const targetMatrix, 
                                 float scalar);

/// @brief Multiply a scalar with a matrix.
/// @param targetMatrix Pointer of the matrix subtracting scalar from
/// @param scalar The multiplying value
/// @return 0 if successfully copied, otherwise 1.
int matrixMultiplyScalar(struct Matrix *const targetMatirx, float scalar);

/// @brief Multiply a scalar with a matrix, with existence check.
/// @param targetMatrix Pointer of the matrix subtracting scalar from
/// @param scalar The multiplying value
/// @return 0 if successfully copied, otherwise 1.
int safeMatrixMultiplyScalar(struct Matrix *const targetMatrix,
                             float scalar);

/// @brief Check whether two matrix is euqal or not by compairing elements.
/// @param a Pointer of one matrix
/// @param b Pointer of another one matrix
/// @return 1 if two matrix is equal, otherwise 0.
int matrixIsEqual(const struct Matrix *const a, const struct Matrix *const b);

/*
    Properties of matrix
*/

/// @brief Find the maximum element of a matrix.
/// @param srcMatrix Pointer of the matrix
/// @return maximum element value if success, else __FLT_MIN__
float matrixMax(const struct Matrix *const srcMatrix);

/// @brief Find the maximum element of a matrix, with existence check.
/// @param srcMatrix Pointer of the matrix
/// @return maximum element value if success, else __FLT_MIN__
float safeMatrixMax(const struct Matrix *const srcMatrix);

/// @brief Find the minimum element of a matrix.
/// @param srcMatrix Pointer of the matrix
/// @return minimum element value if success, else __FLT_MAX__;
float matrixMin(const struct Matrix *const srcMatrix);

/// @brief Find the minimum element of a matrix, with existence check.
/// @param srcMatrix Pointer of the matrix
/// @return minimum element value if success, else __FLT_MAX__;
float safeMatrixMin(const struct Matrix *const srcMatrix);

/// @brief Find the index of maximum element of a matrix
/// @param srcMatrix Pointer of the matrix
/// @param iMax Pointer of the row index of the maximum, for the first one
/// @param jMax Pointer of the column index of the minimum, for the first one. 
/// @note If the matrix cannot be access, iMax and jMax will be (0, 0)
void matrixMaxIndex(const struct Matrix *const srcMatrix, 
                    size_t *iMax, size_t *jMax);

/// @brief Find the index of maximum element of a matrix, with existence check. If the matrix cannot be access, iMax and jMax will be (0, 0).
/// @param srcMatrix Pointer of the matrix
/// @param iMax Pointer of the row index of the maximum, for the first one
/// @param jMax Pointer of the column index of the minimum, for the first one
void matrixMinIndex(const struct Matrix *const srcMatrix, 
                    size_t *iMin, size_t *jMin);


/*
    Matrix basic opertaions
*/
/// @brief Swap two rows of a matrix.
/// @param targetMatrix Pointer of the target matrix
/// @param a One row index of the matrix
/// @param b Another row index of the matrix
/// @return 0 if successfully swapped, otherwise 1.
int matrixSwapRow(struct Matrix *const targetMatrix,
                   const size_t a, const size_t b);

/// @brief Swap two rows of a matrix, with existence check.
/// @param targetMatrix Pointer of the target matrix
/// @param a One row index of the matrix
/// @param b Another row index of the matrix
/// @return 0 if successfully swapped, otherwise 1.
int safeMatrixSwapRow(struct Matrix *const targetMatrix,
                      const size_t a, const size_t b);

/// @brief Swap two columns of a matrix.
/// @param targetMatrix Pointer of the target matrix
/// @param a One column index of the matrix
/// @param b Another column index of the matrix
/// @return 0 if successfully swapped, otherwise 1.
int matrixSwapColumn(struct Matrix *const targetMatrix,
                      const size_t a, const size_t b);

/// @brief Swap two columns of a matrix, with existence check.
/// @param targetMatrix Pointer of the target matrix
/// @param a One column index of the matrix
/// @param b Another column index of the matrix
/// @return 0 if successfully swapped, otherwise 1.
int safeMatrixSwapColumn(struct Matrix *const targetMatrix,
                         const size_t a, const size_t b);

/// @brief Add a row multiply a scalar to another row
/// @param targetMarix Pointer of the target matrix
/// @param a One row index of the matrix
/// @param b Another one row index of the matrix
/// @param s Scalar, b = b + a * s
/// @return 0 if successfully added, otherwise 1.
int matrixAddRow(struct Matrix *const targetMatrix,
                 const size_t a, const size_t b, const float s);

/// @brief Add a row multiply a scalar to another row, with existence check.
/// @param targetMarix Pointer of the target matrix
/// @param a One row index of the matrix
/// @param b Another one row index of the matrix
/// @param s Scalar, b = b + a * s
/// @return 0 if successfully added, otherwise 1.
int safeMatrixAddRow(struct Matrix *const targetMatrix,
                     const size_t a, const size_t b, const float s);

/// @brief Add a column multiply a scalar to another column.
/// @param targetMarix Pointer of the target matrix
/// @param a One column index of the matrix
/// @param b Another one column index of the matrix
/// @param s Scalar, b = b + a * s
/// @return 0 if successfully added, otherwise 1.
int matrixAddColumn(struct Matrix *const targetMatrix,
                    const size_t a, const size_t b, const float s);

/// @brief Add a column multiply a scalar to another column, with existence check.
/// @param targetMarix Pointer of the target matrix
/// @param a One column index of the matrix
/// @param b Another one column index of the matrix
/// @param s Scalar, b = b + a * s
/// @return 0 if successfully added, otherwise 1.
int safeMatrixAddColumn(struct Matrix *const targetMatrix,
                        const size_t a, const size_t b, const float s);

/// @brief Multiply a row with a scalar.
/// @param targetMatrix Pointer of the target matrix
/// @param a Index of the row
/// @param s The scalar
/// @return 0 if successfully added, otherwise 1.
int matrixRowMultiplyScalar(struct Matrix *const targetMatrix,
                            const size_t a, const float s);

/// @brief Multiply a row with a scalar, with existsence check.
/// @param targetMatrix Pointer of the target matrix
/// @param a Index of the row
/// @param s The scalar
/// @return 0 if successfully added, otherwise 1.
int safeMatrixRowMultiplyScalar(struct Matrix *const targetMatrix,
                            const size_t a, const float s);

/// @brief Multiply a column with a scalar.
/// @param targetMatrix Pointer of the target matrix
/// @param a Index of the column
/// @param s The scalar
/// @return 0 if successfully added, otherwise 1.
int matrixColMultiplyScalar(struct Matrix *const targetMatrix,
                            const size_t a, const float s);

/// @brief Multiply a column with a scalar, with existsence check.
/// @param targetMatrix Pointer of the target matrix
/// @param a Index of the column
/// @param s The scalar
/// @return 0 if successfully added, otherwise 1.
int safeMatrixColMultiplyScalar(struct Matrix *const targetMatrix,
                                const size_t a, const float s);
#endif
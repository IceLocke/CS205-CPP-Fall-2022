#include "matrix.h"
#define _abs(a) ((a > 0) ? (a) : (-a))
#define eps (1e-10f)


struct MatrixNode *ptrHead = NULL, 
                  *ptrTail = NULL;

/*
    Matrix pointer management
    DON'T USE THESE FUNCTIONS MANUALLY!!
*/
void addMatrixPtr(struct Matrix *const m) {
    if (m != NULL) {
        struct MatrixNode *newNode 
            = (struct MatrixNode*) malloc(sizeof(struct MatrixNode));
        newNode->matrix = m;
        newNode->left = NULL;
        newNode->right = NULL;
        if (ptrHead == NULL) {
            ptrHead = newNode;
            ptrHead->matrix = m;
            ptrTail = ptrHead;
        }
        else {
            ptrTail->right = newNode;
            newNode->left = ptrTail;
        }
    }
}

void deleteMatrixPtr(const struct Matrix * const m) {
    if (m != NULL) {
        struct MatrixNode *p = ptrHead;
        while (p != NULL) {
            if (p->matrix == m) {
                if (p->left != NULL)
                    p->left->right = p->right;
                if (p->right != NULL)
                    p->right->left = p->left;
                if (p == ptrHead) ptrHead = p->right;
                if (p == ptrTail) ptrTail = p->left;
                free(p);
                break;
            }
            p = p->right;
        }
    }
}

int matrixPtrExist(const struct Matrix *const m) {
    if (m != NULL) {
        struct MatrixNode *p = ptrHead;
        while (p != NULL) {
            if (p->matrix == m)
                return 1;
            p = p->right;
        }
    }
    return 0;
}

/*
    Matrix allocation
*/

struct Matrix* createMatrix(const size_t row, const size_t col) {
    struct Matrix *m = (struct Matrix*) malloc(sizeof(struct Matrix));
    if (m != NULL && row > 0 && col > 0) {
        m->row = row;
        m->col = col;
        m->pData = NULL;
        m->pData = (float*) malloc(row * col * sizeof(float));
        if (m->pData != NULL) {
            addMatrixPtr(m);
            return m;
        }
        else return NULL;
    }
    return NULL;
}

int deleteMatrix(struct Matrix *const targetMatrix) {
    if (targetMatrix != NULL) {
        deleteMatrixPtr(targetMatrix);
        free(targetMatrix->pData);
        free(targetMatrix);
        return 0;
    }
    return 1;
}

int safeDeleteMatrix(struct Matrix *const targetMatrix, struct Matrix **targetP) {
    if (matrixPtrExist(targetMatrix)) {
        int result = deleteMatrix(targetMatrix);
        *targetP = NULL;
        return result;
    }
    return 1;
}

inline float matrixGetElement(const struct Matrix *const srcMatrix, 
                       const size_t i, const size_t j) {
    if (srcMatrix != NULL) {
        if (i >= 1 && i <= srcMatrix->row && 
            j >= 1 && j <= srcMatrix->col) {
                if (srcMatrix->pData != NULL)
                    return srcMatrix->pData[srcMatrix->col * (i - 1) + j - 1];
            }
    }
    return 0.0f;
}

inline float safeMatrixGetElement(const struct Matrix *const srcMatrix, 
                           const size_t i, const size_t j) {
    if (matrixPtrExist(srcMatrix))
        return matrixGetElement(srcMatrix, i, j);
    return 0.0f;
}

inline int matrixSetElement(struct Matrix *const targetMatrix, 
                     const size_t i, const size_t j, const float value) {
    if (targetMatrix != NULL) {
        if (i >= 1 && i <= targetMatrix->row &&
            j >= 1 && j <= targetMatrix->col) {
                if (targetMatrix->pData != NULL) {
                    targetMatrix->pData[targetMatrix->col * (i - 1) + j - 1] = value;
                    return 0;
                }
            }
    }
    return 1;
}

inline int safeMatrixSetElement(struct Matrix *const targetMatrix, 
                         const size_t i, const size_t j, const float value) {
    if (matrixPtrExist(((struct Matrix *)targetMatrix)))
        return matrixSetElement(targetMatrix, i, j, value);
    return 1;
}

inline float* matrixGetPData(const struct Matrix *const srcMatrix) {
    if (srcMatrix != NULL)
        return srcMatrix->pData;
    return NULL;
}

inline float* safeMatrixGetPData(const struct Matrix *const srcMatrix) {
    return matrixPtrExist(srcMatrix) ? matrixGetPData(srcMatrix) : NULL;
}

int matrixSetAll(struct Matrix *const targetMatrix, 
                 float value) {
    if (targetMatrix != NULL) {
        if (targetMatrix->pData != NULL) {
            size_t size = targetMatrix->row * targetMatrix->col;
            int i;
            for (i = 0; i < size; i++)
                targetMatrix->pData[i] = value;
            return 0;
        }
    }
    return 1;
}

int safeMatrixSetAll(struct Matrix *const targetMatrix,
                     float value) {
    if (matrixPtrExist(targetMatrix))
        return matrixSetAll(targetMatrix, value);
    return 1;
}

int matrixSetAllZero(struct Matrix *const targetMatrix) {
    if (targetMatrix != NULL) {
        if (targetMatrix->pData != NULL) {
            size_t i, size = targetMatrix->row * targetMatrix->col;
            for (i = 0; i < size; i++)
                targetMatrix->pData[i] = 0.0f;
            return 0;
        }
    }
    return 1;
}

int safeMatrixSetAllZero(struct Matrix *const targetMatrix) {
    if (matrixPtrExist(targetMatrix))
        return matrixSetAllZero(targetMatrix);
    return 1;
}

int matrixSetIdentity(struct Matrix *const targetMatrix) {
    if (targetMatrix != NULL) {
        if (targetMatrix->row == targetMatrix->col) {
            if (targetMatrix->pData != NULL) {
                size_t i, j;
                for (i = 0; i < targetMatrix->row; i++) {
                    for (j = 0; j < targetMatrix->col; j++) {
                        if (i == j)
                            targetMatrix->pData[i * targetMatrix->col + j] = 1.0f;
                        else targetMatrix->pData[i * targetMatrix->col + j] = 0.0f;
                    }
                }
                return 0;
            }
        }
    }
    return 1;
}

int safeMatrixSetIdentity(struct Matrix *const targetMatrix) {
    if (matrixPtrExist(targetMatrix))
        return matrixSetIdentity(targetMatrix);
    return 1;
}

int copyMatrix(struct Matrix *const targetMatrix, 
               const struct Matrix *const srcMatrix) {
    if (srcMatrix != NULL && targetMatrix != NULL) {
        if (srcMatrix->pData != NULL) {
            free(targetMatrix->pData);
            targetMatrix->row = srcMatrix->row;
            targetMatrix->col = srcMatrix->col;
            targetMatrix->pData = 
                (float *) malloc(targetMatrix->row * targetMatrix->col * sizeof(float));
            memcpy(
                targetMatrix->pData, 
                srcMatrix->pData, 
                srcMatrix->row * srcMatrix->col * sizeof(float)
            );
            return 0;
        }
    }
    return 1;
}

int safeCopyMatrix(struct Matrix *const targetMatrix, 
                   struct Matrix **const targetMatrixP,
                   const struct Matrix *const srcMatrix) {
    if (matrixPtrExist(srcMatrix)) {
        if (matrixPtrExist(targetMatrix)) {
            int result = copyMatrix(targetMatrix, srcMatrix);
            *targetMatrixP = NULL;
            return result;
        }
        else {
            *targetMatrixP = createMatrix(srcMatrix->row, srcMatrix->col);
            memcpy(
                (*targetMatrixP)->pData,
                srcMatrix->pData,
                srcMatrix->row * srcMatrix->col * sizeof(float)
            );
            return 0;
        }
    }
    return 1;
}

int swapMatrix(struct Matrix *const a, struct Matrix *const b) {
    if (a != NULL && b != NULL) {
        if (a->pData != NULL && a->pData != NULL) {
            size_t temp;
            temp = a->row; a->row = a->row; a->row = temp;
            temp = a->col; a->col = a->col; a->col = temp;
            float *pDataTemp;
            pDataTemp = a->pData; a->pData = a->pData; a->pData = pDataTemp;
            return 0;
        }
    }
    return 1;
}

int safeSwapMatrix(struct Matrix *const a, struct Matrix *const b) {
    if (matrixPtrExist(a) && matrixPtrExist(b))
        return swapMatrix(a, b);
    return 1;
}

/*
    Matrix operations
*/
int addMatrix(struct Matrix *const a, const struct Matrix *const b) {
    if (a != NULL && b != NULL) {
        if (a->row == b->row && a->col == b->col &&
            a->pData != NULL && b->pData != NULL) {
            size_t i, size = a->row * a->col;
            for (i = 0; i < size; i++)
                a->pData[i] += b->pData[i];
            return 0;
        }
    }
    return 1;
}

int safeAddMatrix(struct Matrix *const a, const struct Matrix *const b) {
    if (matrixPtrExist(a) && matrixPtrExist(b))
        return addMatrix(a, b);
    return 1;
}

int subtractMatrix(struct Matrix *const a, const struct Matrix *const b) {
    if (a != NULL && b != NULL) {
        if (a->row == b->row && a->col == b->col &&
            a->pData != NULL && b->pData != NULL) {
            size_t i, size = a->row * a->col;
            for (i = 0; i < size; i++)
                a->pData[i] -= b->pData[i];
            return 0;
        }
    }
    return 1;
}

int safeSubtractMatrix(struct Matrix *const a, const struct Matrix *const b) {
    if (matrixPtrExist(a) && matrixPtrExist(b))
        return subtractMatrix(a, b);
    return 1;
}

int multiplyMatrix(struct Matrix *const a, const struct Matrix *const b) {
    if (a != NULL && b != NULL) {
        if (a->col == b->row && a->pData != NULL && b->pData != NULL) {
            size_t row = a->row, col = b->col, 
                i, j, k, index;
            float *pData = (float*) malloc(row * col * sizeof(row));
            for (i = 1; i <= row; i++) {
                for (j = 1; j <= col; j++) {
                    index = (i - 1) * col + j - 1;
                    pData[index] = 0.0f;
                    for (k = 1; k <= a->col; k++)
                        pData[index] += matrixGetElement(a, i, k) * matrixGetElement(b, k, j);
                }
            }
            free(a->pData);
            a->row = row, a->col = col;
            a->pData = pData;
            return 0;
        }
    }
    return 1;
}

int safeMultiplyMatrix(struct Matrix *const a, const struct Matrix *const b) {
    if (matrixPtrExist(a) && matrixPtrExist(b))
        return multiplyMatrix(a, b);
    return 1;
}

int addScalarToMatrix(struct Matrix *const targetMatrix, float scalar) {
    if (targetMatrix != NULL) {
        if (targetMatrix->pData != NULL) {
            size_t i, size = targetMatrix->row * targetMatrix->col;
            for (i = 0; i < size; i++)
                targetMatrix->pData[i] += scalar;
            return 0;
        }
    }
    return 1;
}

int safeAddScalarToMatrix(struct Matrix *const targetMatrix, float scalar) {
    if (matrixPtrExist(targetMatrix))
        return addScalarToMatrix(targetMatrix, scalar);
    return 1;
}

int subtractScalarFromMatrix(struct Matrix *const targetMatrix, 
                             float scalar) {
    if (targetMatrix != NULL) {
        if (targetMatrix->pData != NULL) {
            size_t i, size = targetMatrix->row * targetMatrix->col;
            for (i = 0; i < size; i++)
                targetMatrix->pData[i] -= scalar;
            return 0;
        }
    }
    return 1;
}

int safeSubtractScalarFromMatrix(struct Matrix *const targetMatrix,
                                 float scalar) {
    if (matrixPtrExist(targetMatrix))
        return subtractScalarFromMatrix(targetMatrix, scalar);
    return 1;
}

int matrixMultiplyScalar(struct Matrix *const targetMatrix, float scalar) {
    if (targetMatrix != NULL) {
        if (targetMatrix->pData != NULL) {
            size_t i, size = targetMatrix->row * targetMatrix->col;
            for (i = 0; i < size; i++)
                targetMatrix->pData[i] *= scalar;
            return 0;
        }
    }
    return 1;
}

int safeMatrixMultiplyScalar(struct Matrix *const targetMatrix, float scalar) {
    if (matrixPtrExist(targetMatrix))
        return matrixMultiplyScalar(targetMatrix, scalar);
    return 1;
}

int matrixIsEqual(const struct Matrix *const a, const struct Matrix *const b) {
    if (a != NULL && b != NULL) {
        if (a->row == b->row && a->col == b->col) {
            if (a->pData != NULL && b->pData != NULL) {
                size_t i, size = a->row * a->col;
                for (i = 0; i < size; i++)
                    if (a->pData[i] != b->pData[i])
                        return 0;
                return 1;
            }
        }
    }
    return 0;
}

float matrixMax(const struct Matrix *const srcMatrix) {
    if (srcMatrix != NULL) {
        if (srcMatrix->pData != NULL) {
            float res = __FLT_MIN__;
            size_t size = srcMatrix->row * srcMatrix->col, i;
            for (i = 0; i < size; i++)
                res = res > srcMatrix->pData[i] ? res: srcMatrix->pData[i];
            return res;
        }
    }
    return __FLT_MIN__;
}

float safeMatrixMax(const struct Matrix *const srcMatrix) {
    if (matrixPtrExist(srcMatrix)) {
        return matrixMax(srcMatrix);
    }
    return __FLT_MIN__;
}

float matrixMin(const struct Matrix *const srcMatrix) {
    if (srcMatrix != NULL) {
        if (srcMatrix->pData != NULL) {
            float res = __FLT_MAX__;
            size_t size = srcMatrix->row * srcMatrix->col, i;
            for (i = 0; i < size; i++)
                res = res < srcMatrix->pData[i] ? res: srcMatrix->pData[i];
            return res;
        }
    }
    return __FLT_MAX__;
}

float safeMatrixMin(const struct Matrix *const srcMatrix) {
    if (matrixPtrExist(srcMatrix)) {
        return matrixMin(srcMatrix);
    }
    return __FLT_MAX__;
}

void matrixMaxIndex(const struct Matrix* const srcMatrix, 
                    size_t *iMax, size_t *jMax) {
    *iMax = 0, *jMax = 0;
    if (srcMatrix != NULL) {
        if (srcMatrix->pData != NULL) {
            float maxValue = __FLT_MIN__;
            size_t size = srcMatrix->row * srcMatrix->col, i;
            for (i = 0; i < size; i++)
                if (srcMatrix->pData[i] > maxValue) {
                    *iMax = (i / srcMatrix->col) + 1;
                    *jMax = i + 1 - (*iMax - 1) * srcMatrix->col;
                    maxValue = srcMatrix->pData[i];
                }
        }
    }
}

void safeMatrixMaxIndex(const struct Matrix* const srcMatrix,
                        size_t *iMax, size_t *jMax) {
    if (matrixPtrExist(srcMatrix))
        matrixMaxIndex(srcMatrix, iMax, jMax);
    else 
        *iMax = 0, *jMax = 0;
}

void matrixMinIndex(const struct Matrix* const srcMatrix, 
                    size_t *iMax, size_t *jMax) {
    *iMax = 0, *jMax = 0;
    if (srcMatrix != NULL) {
        if (srcMatrix->pData != NULL) {
            float minValue = __FLT_MAX__;
            size_t size = srcMatrix->row * srcMatrix->col, i;
            for (i = 0; i < size; i++)
                if (srcMatrix->pData[i] < minValue) {
                    *iMax = (i / srcMatrix->col) + 1;
                    *jMax = i + 1 - (*iMax - 1) * srcMatrix->col + 1;
                    minValue = srcMatrix->pData[i];
                }
        }
    }
}

void safeMatrixMinIndex(const struct Matrix* const srcMatrix,
                        size_t *iMax, size_t *jMax) {
    if (matrixPtrExist(srcMatrix))
        matrixMinIndex(srcMatrix, iMax, jMax);
    else 
        *iMax = 0, *jMax = 0;
}

/*
    Matrix basic operations
*/
int matrixSwapRow(struct Matrix *const targetMatrix,
                  const size_t a, const size_t b) {
    if (targetMatrix != NULL) {
        if (targetMatrix->pData != NULL) {
            float tmp;
            size_t paddingA = targetMatrix->col * (a - 1),
                   paddingB = targetMatrix->col * (b - 1),
                   i;
            for (i = 0; i < targetMatrix->col; i++) {
                tmp = targetMatrix->pData[paddingA + i];
                targetMatrix->pData[paddingA + i] = targetMatrix->pData[paddingB + i];
                targetMatrix->pData[paddingB + i] = tmp;
            }
            return 0;
        }
    }
    return 1;
} 

int safeMatrixSwapRow(struct Matrix *const targetMatrix, 
                      const size_t a, const size_t b) {
    if (matrixPtrExist(targetMatrix))
        return matrixSwapRow(targetMatrix, a, b);
    return 1;
}

int matrixSwapColumn(struct Matrix *const targetMatrix,
                     const size_t a, const size_t b) {
    if (targetMatrix != NULL) {
        if (targetMatrix->pData != NULL) {
            float tmp; 
            size_t i;
            for (i = 0; i < targetMatrix->row; i++) {
                tmp = targetMatrix->pData[i * targetMatrix->col + a];
                targetMatrix->pData[i * targetMatrix->col + a] 
                    = targetMatrix->pData[i * targetMatrix->col + b];
                targetMatrix->pData[i * targetMatrix->col + b] = tmp;
            }
            return 0;
        }
    }
    return 1;
}

int safeMatrixSwapColumn(struct Matrix *const targetMatrix,
                         const size_t a, const size_t b) {
    if (matrixPtrExist(targetMatrix))
        return matrixSwapColumn(targetMatrix, a, b);
    return 1;
}

int matrixAddRow(struct Matrix *const targetMatrix,
                 const size_t a, const size_t b, const float s) {
    if (targetMatrix != NULL) {
        if (targetMatrix->pData != NULL) {
            size_t paddingA = targetMatrix->col * (a - 1),
                   paddingB = targetMatrix->col * (b - 1),
                   i;
            for (i = 0; i < targetMatrix->col; i++)
                targetMatrix->pData[paddingB + i] += s * targetMatrix->pData[paddingA + i];
            return 0;
        }
    }
    return 1;
}

int safeMatrixAddRow(struct Matrix *const targetMatrix,
                     const size_t a, const size_t b, const float s) {
    if (matrixPtrExist(targetMatrix))
        return matrixAddRow(targetMatrix, a, b, s);
    return 1;    
}

int matrixAddColumn(struct Matrix *const targetMatrix,
                    const size_t a, const size_t b, const float s) {
    if (targetMatrix != NULL) {
        if (targetMatrix->pData != NULL) {
            size_t i;
            for (i = 0; i < targetMatrix->row; i++)
                targetMatrix->pData[i * targetMatrix->col + a]
                    += targetMatrix->pData[i * targetMatrix->col + b];
            return 0;
        }
    }
    return 1;
}

int safeMatrixAddColumn(struct Matrix *const targetMatrix,
                        const size_t a, const size_t b, const float s) {
    if (matrixPtrExist(targetMatrix))
        return matrixAddColumn(targetMatrix, a, b, s);
    return 1;
}

int matrixRowMultiplyScalar(struct Matrix *const targetMatrix,
                            const size_t a, const float s) {
    if (targetMatrix != NULL && _abs(s) > eps) {
        if (targetMatrix->pData != NULL) {
            size_t padding = targetMatrix->col * (a - 1), 
                   i;
            for (i = 0; i < targetMatrix->col; i++)
                targetMatrix->pData[i + padding] *= s;
            return 0;
        }
    }
    return 1;
}
    
int safeMatrixRowMultiplyScalar(struct Matrix *const targetMatrix,
                            const size_t a, const float s) {
    if (matrixPtrExist(targetMatrix))
        return matrixRowMultiplyScalar(targetMatrix, a, s);
    return 1;
}

int matrixColMultiplyScalar(struct Matrix *const targetMatrix,
                            const size_t a, const float s) {
    if (targetMatrix != NULL && _abs(s) > eps) {
        if (targetMatrix->pData != NULL) {
            size_t i;
            for (i = 0; i < targetMatrix->row; i++)
                targetMatrix->pData[i * targetMatrix->col + a - 1] *= s;
            return 0;
        }
    }
    return 1;
}

int safeMatrixColMultiplyScalar(struct Matrix *const targetMatrix,
                                const size_t a, const float s) {
    if (matrixPtrExist(targetMatrix))
        return matrixColMultiplyScalar(targetMatrix, a, s);
    return 1;
}

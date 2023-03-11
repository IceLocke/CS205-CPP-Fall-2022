# CS205 Project 3 Report

**Name:**
## Part 1 - Analysis
本 Project 要求使用 C 实现一个简单的矩阵库。在参考 GSL 的 vector 库后，我考虑设计以下结构体/函数。

### 结构体
```c
struct Matrix {
    size_t row, col;    // 矩阵的行和列
    float *pData;       // 矩阵数据数组的指针
};
```
由于考虑了内存安全问题，我使用双向链表维护一个指针列表，保证用户在使用 safe 方法访问矩阵时不出现内存错误。以下是链表节点的结构体原型：

```c
struct MatrixNode {
    struct Matrix *matrix;      // 合法的矩阵指针
    struct MatrixNode *left;    // 左边的节点指针
    struct MatrixNode *right;   // 右边的节点指针
};
```

### 函数
对于查询类函数，使用查询值作为返回值；对于用户使用的修改类函数，使用 `0/1` 作为返回值代表操作是否成功。同时对于大部分函数实现了，速度较快的普通方法和进行指针合法性检查的安全方法，在这里只列出部分普通方法。

#### Matrix Pointer Management
函数原型|描述
---|---
`void addMatrixPtr(struct Matrix *const m)`|在链表中添加一个合法的矩阵指针
`void deleteMatrixPtr(const struct Matrix *const m)`|在链表中删除一个存在的合法的矩阵指针
`int matrixPtrExist(const struct Matrix *const m)`|判断矩阵指针是否在指针表中存在

#### Matrix Allocation
函数原型|描述
---|---
`struct Matrix* createMatrix(const size_t row, const size_t col)`| 指定行列，创建一个新的矩阵
`int deleteMatrix(struct Matrix *const targetMatrix)`|删除一个矩阵
`int safeDeleteMatrix(struct Matrix *const targetMatrix, struct Matrix **targetP);`|安全地删除一个矩阵，并将原指针赋为NULL

#### Matrix Elements Accessing
函数原型|描述
---|---
`float matrixGetElement(const struct Matrix *const srcMatrix, const size_t i, const size_t j);`|获得矩阵下标为(i, j)的元素
`int matrixSetElement(struct Matrix *const targetMatrix, const size_t i, const size_t j, const float value)`|将矩阵下标为(i,j)的元素设置为value
`float* matrixGetPData(const struct Matrix *const srcMatrix)`|获得矩阵数据数组的指针

#### Matrix Initializing
函数原型|描述
---|---
`int matrixSetAll(struct Matrix *const targetMatrix, float value)`|初始化矩阵所有元素为value
`int matrixSetAllZero(struct Matrix *const targetMatrix)`|初始化矩阵所有元素为0
`int matrixSetIdentity(struct Matrix *const targetMatrix)`|初始化矩阵为单位矩阵

#### Matrix Copying
函数原型|描述
---|---
`int copyMatrix(struct Matrix *const targetMatrix, const struct Matrix *const srcMatrix);`|将一个矩阵的所有信息复制到另一个矩阵中
`int swapMatrix(struct Matrix *const a, struct Matrix *const b)`|交换两个矩阵

### Matrix Operations
函数原型|描述
---|---
`int addMatrix(struct Matrix *const a, const struct Matrix *const b)`|将两个大小相同的矩阵相加
`int subtractMatrix(struct Matrix *const a, const struct Matrix *const b)`|将两个大小相同的矩阵相减
`int multiplyMatrix(struct Matrix *const a, const struct Matrix *const b)`|将两个符合矩阵乘法要求的矩阵相乘
`int addScalarToMatrix(struct Matrix *const targetMatrix, float scalar)`|将一个标量加到矩阵的每一个元素上
`int subtractScalarFromMatrix(struct Matrix *const targetMatrix, float scalar)`|从矩阵的每一个元素减去一个标量
`int matrixMultiplyScalar(struct Matrix *const targetMatirx, float scalar)`|将矩阵的每一个元素乘上一个标量
`int matrixIsEqual(const struct Matrix *const a, const struct Matrix *const b)`|判断两个矩阵是否相等
`int matrixSwapRow(struct Matrix *const targetMatrix, const size_t a, const size_t b)`|将矩阵的两行交换
`int matrixSwapColumn(struct Matrix *const targetMatrix, const size_t a, const size_t b)`|将矩阵的两列交换
`int matrixAddRow(struct Matrix *const targetMatrix, const size_t a, const size_t b, const float s)`|将矩阵的某行乘上一个标量加到另外一行上
`int matrixAddColumn(struct Matrix *const targetMatrix, const size_t a, const size_t b, const float s)`|将矩阵的某列乘上一个标量加到另外一列上
`int matrixRowMultiplyScalar(struct Matrix *const targetMatrix, const size_t a, const float s)`|将矩阵的某行乘上一个标量
`int matrixColMultiplyScalar(struct Matrix *const targetMatrix, const size_t a, const float s)`|将矩阵的某列乘上一个标量

#### Matrix Properties
函数原型|描述
---|---
`float matrixMax(const struct Matrix *const srcMatrix)`|返回矩阵元素的最大值
`float matrixMin(const struct Matrix *const srcMatrix)`|返回矩阵元素的最小值
`void matrixMaxIndex(const struct Matrix *const srcMatrix, size_t *iMax, size_t *jMax);`|将矩阵元素最大值的下标存储在`*iMax`和`*jMax`中
`void matrixMinIndex(const struct Matrix *const srcMatrix, size_t *iMax, size_t *jMax);`|将矩阵元素最小值的下标存储在`*iMax`和`*jMax`中
---
同时，为了用户使用方便，我使用了 Doxygen 进行文档生成，对函数具体功能、参数、返回值都进行了详细的描述，使用支持 Doxygen 的编辑器/IDE时将会自动显示。
```c
/// @brief Copy a matrix to an another matrix, with existence check. \n
/// @brief If the targetMatrix is not exist, the function will automatically create one.
/// @param targetMatrix Pointer of the matrix copying to
/// @param targetMatrixP Pointer of pointer of the matrix copying to
/// @param srcMatrix Pointer of the matrix copying from
/// @return 0 if successfully copied, otherwise 1.
int safeCopyMatrix(struct Matrix *const targetMatrix,
                   struct Matrix **const targetMatrixP,
                   const struct Matrix *const srcMatrix);
```

## Part 2 - Code
**这里仅展示进行指针表维护和安全性检查的部分代码。其他代码由于比较简单没有展示。**
### 指针表维护
```c
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
```
### 安全性检查（样例）
```c
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
```

## Part 3 - Tests
由于代码功能较为独立，我编写了一系列模块测试函数（见`unit_test.c`）对模块功能进行测试。
### Test 1 - Allocation Test
```c
struct Matrix *m = createMatrix(4, 4);
matrixSetAllZero(m);
printMatrix(m);
safeDeleteMatrix(m, &m);
safeDeleteMatrix(m, &m);
deleteMatrix(m);
```
Output:
```
### Allocation Test
0.000000 0.000000 0.000000 0.000000 
0.000000 0.000000 0.000000 0.000000 
0.000000 0.000000 0.000000 0.000000 
0.000000 0.000000 0.000000 0.000000 
```
### Test 2 - Initialzing Test
```c
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
```
Output:
```
// Accessing elements through matrixGetElement()
1.000000 0.000000 0.000000 0.000000 
0.000000 1.000000 0.000000 0.000000 
0.000000 0.000000 1.000000 0.000000 
0.000000 0.000000 0.000000 1.000000 

// Reset a elements
1.000000 0.000000 0.000000 0.000000 
0.000000 1.000000 0.000000 0.000000 
0.000000 0.000000 5.000000 0.000000 
0.000000 0.000000 0.000000 1.000000 

// Get *pData
0x14ec030 0x14ec030
```

### Test 3 - Matrix Copying Test
```c
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
```
Output:
```
// Copying
1.000000 0.000000 0.000000 0.000000 
0.000000 1.000000 0.000000 0.000000 
0.000000 0.000000 1.000000 0.000000 
0.000000 0.000000 0.000000 1.000000 

1.000000 0.000000 0.000000 0.000000 
0.000000 1.000000 0.000000 0.000000 
0.000000 0.000000 1.000000 0.000000 
0.000000 0.000000 0.000000 1.000000 

// Swapping
1.000000 0.000000 0.000000 0.000000 
0.000000 1.000000 0.000000 0.000000 
0.000000 0.000000 1.000000 0.000000 
0.000000 0.000000 0.000000 1.000000 

1.000000 0.000000 0.000000 0.000000 
0.000000 1.000000 0.000000 0.000000 
0.000000 0.000000 1.000000 0.000000 
0.000000 0.000000 0.000000 1.000000 
```

### Test 4 - Matrix Operation Test
```c
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
```
Output:
```
1.000000 1.000000 1.000000 1.000000 
1.000000 1.000000 1.000000 1.000000 
1.000000 1.000000 1.000000 1.000000 
1.000000 1.000000 1.000000 1.000000 

1.000000 0.000000 0.000000 0.000000 
0.000000 1.000000 0.000000 0.000000 
0.000000 0.000000 1.000000 0.000000 
0.000000 0.000000 0.000000 1.000000 

2.000000 1.000000 1.000000 1.000000 
1.000000 2.000000 1.000000 1.000000 
1.000000 1.000000 2.000000 1.000000 
1.000000 1.000000 1.000000 2.000000 

0.000000 0.000000 0.000000 0.000000 
0.000000 0.000000 0.000000 0.000000 
0.000000 0.000000 0.000000 0.000000 
0.000000 0.000000 0.000000 0.000000 

1.000000 1.000000 1.000000 1.000000 
1.000000 1.000000 1.000000 1.000000 
1.000000 1.000000 1.000000 1.000000 
1.000000 1.000000 1.000000 1.000000 

6.000000 6.000000 6.000000 6.000000 
6.000000 6.000000 6.000000 6.000000 
6.000000 6.000000 6.000000 6.000000 
6.000000 6.000000 6.000000 6.000000 

1.000000 1.000000 1.000000 1.000000 
1.000000 1.000000 1.000000 1.000000 
1.000000 1.000000 1.000000 1.000000 
1.000000 1.000000 1.000000 1.000000 

10.000000 10.000000 10.000000 10.000000 
10.000000 10.000000 10.000000 10.000000 
10.000000 10.000000 10.000000 10.000000 
10.000000 10.000000 10.000000 10.000000 

m1 and m2 are equal: 1
```

### Test 5 - Matrix Properties Test
```c
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
```
Output:
```
4.000000 9.000000 2.000000 6.000000 
6.000000 0.000000 6.000000 0.000000 
9.000000 4.000000 4.000000 4.000000 
6.000000 6.000000 9.000000 8.000000 

9.000000
1 2
0.000000
2 3
```

### Test 6 - Matrix Basic Operation Test
```c
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
```
Output:
```
4.000000 9.000000 2.000000 6.000000 
6.000000 0.000000 6.000000 0.000000 
9.000000 4.000000 4.000000 4.000000 
6.000000 6.000000 9.000000 8.000000 

6.000000 0.000000 6.000000 0.000000 
4.000000 9.000000 2.000000 6.000000 
9.000000 4.000000 4.000000 4.000000 
6.000000 6.000000 9.000000 8.000000 

6.000000 6.000000 0.000000 0.000000 
4.000000 2.000000 9.000000 6.000000 
9.000000 4.000000 4.000000 4.000000 
6.000000 9.000000 6.000000 8.000000 

6.000000 6.000000 0.000000 0.000000 
10.000000 8.000000 9.000000 6.000000 
9.000000 4.000000 4.000000 4.000000 
6.000000 9.000000 6.000000 8.000000 

6.000000 6.000000 0.000000 0.000000 
10.000000 17.000000 9.000000 6.000000 
9.000000 8.000000 4.000000 4.000000 
6.000000 15.000000 6.000000 8.000000 

6.000000 6.000000 0.000000 0.000000 
10.000000 17.000000 9.000000 6.000000 
9.000000 8.000000 4.000000 4.000000 
12.000000 30.000000 12.000000 16.000000 

6.000000 6.000000 0.000000 0.000000 
10.000000 17.000000 9.000000 12.000000 
9.000000 8.000000 4.000000 8.000000 
12.000000 30.000000 12.000000 32.000000 
```

### Test 7 - Safety Test
```c
struct Matrix *m = createMatrix(4, 4);
matrixSetAllZero(m);
deleteMatrix(m);
safeMatrixGetElement(m, 1, 1);
safeMatrixSetElement(m, 1, 1, 1.0f);
```
Output
```c
No falut, passed.
```

## Part 4 - Difficuties & Solution
需要考虑可能出现的异常情况较多。此外还需要维护一个指针表。之后指针表需要使用一个平衡树维护，使用现有的链表维护效率较低。
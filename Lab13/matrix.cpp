#include <iostream>
#include <string>

const int MAXROWS = 5;
const int MAXCOLS = 5;

using std::cout;
using std::endl;
using std::string;

template <typename T>
class Matrix {
private:
    T matrix[MAXROWS][MAXCOLS];
    size_t rows, cols;
public:
    Matrix(size_t row = MAXROWS, size_t col = MAXCOLS): rows(row), cols(col) {}

    void printMatrix() {
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++)
                cout << matrix[i][j] << " ";
            cout << endl;
        } 
    }

    void setMatrix(T m[][MAXCOLS]) {
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++)
                matrix[i][j] = m[i][j];
        } 
    }

    void addMatrix(T m[][MAXCOLS]) {
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++)
                matrix[i][j] += m[i][j];
        } 
    }
};

template <typename T>
void useMatrixTemplate(Matrix<T> &m, T arr1[][MAXCOLS], T arr2[][MAXCOLS]) {
    cout << "Matrix set by first arary: " << endl;
    m.setMatrix(arr1);
    m.printMatrix();

    cout << "Matrix add second arrary: " << endl;
    m.addMatrix(arr2);
    m.printMatrix();
} 

int main() {
    string str1[MAXROWS][MAXCOLS] = {{"a", "b", "c"}, {"d", "e", "f"}};
    string str2[MAXROWS][MAXCOLS] = {{"g", "h", "i"}, {"j", "k", "l"}};

    int num1[MAXROWS][MAXCOLS] ={{1, 2, 3}, {4, 5, 6}};
    int num2[MAXROWS][MAXCOLS] ={{6, 5, 4}, {3, 2, 1}};

    Matrix<string> stringMatrix(2, 3);
    Matrix<int> intMatrix(2, 3);
    
    cout << "Str mat: " << endl;
    useMatrixTemplate(stringMatrix, str1, str2);
    cout << endl << "Int mat: " << endl;
    useMatrixTemplate(intMatrix, num1, num2);
    
    return 0;
}
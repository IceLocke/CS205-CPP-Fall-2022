#include <iostream>
#include <cstdlib>
#include <memory>
using std::cout;
using std::endl;

class Matrix {
private:
    size_t row, col;
    std::shared_ptr<float[]> data;
public:
    void setElement(size_t row, size_t col, float v) {
        data.get()[(row - 1) * this->col + col - 1] = v;
    }
    float getElement(size_t row, size_t col) {
        return data.get()[(row - 1) * this->col + col - 1];
    }
    Matrix(size_t row, size_t col) {
        this->row = row, this->col = col;
        data = std::shared_ptr<float[]>(new float(row * col));
    }
    Matrix(Matrix &m) {
        this->row = m.row, this->col = m.col;
        this->data = m.data;
    }
    Matrix & operator= (Matrix &m) {
        this->row = m.row, this->col = m.col;
        this->data = m.data;
        return *this;
    }
    Matrix & operator+ (Matrix &m) {
        if (this->row == m.row && this->col == m.col) {
            Matrix *res = new Matrix(this->row, this->col);
            for (int i = 1; i <= this->row; i++)
                for (int j = 1; j <= this->col; j++)
                    res->setElement(i, j, this->getElement(i, j) + m.getElement(i, j));
            return *res;
        }
        else return *this;
    }
};

int main() {

    Matrix a(3,4);
    Matrix b(3,4);
    Matrix c = a + b;
    Matrix d = a;
    d = b;

}
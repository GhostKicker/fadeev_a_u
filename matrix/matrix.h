#ifndef MATRIX_H
#define MATRIX_H

#include <cstddef>
using namespace std;

class Matrix {
public:
    Matrix() = default;
    Matrix(const ptrdiff_t& nRow, const ptrdiff_t& nCol);
    Matrix(const Matrix& m);
    ~Matrix();

    void swapWith(Matrix& m);

    ptrdiff_t& length();
    ptrdiff_t& rowNum();
    ptrdiff_t& colNum();

    double& operator()(const ptrdiff_t i, const ptrdiff_t j);
    const double& operator()(const ptrdiff_t i, const ptrdiff_t j) const;
    Matrix& operator=(Matrix& obj);
    Matrix& operator+=(const Matrix& m);
    Matrix& operator-=(const Matrix& m);
    Matrix& operator*=(const Matrix& m);

    long long& determinator();
    Matrix& pow(const Matrix& m, long long& power);
    Matrix& inverse();

private:

    double** ppData_{ nullptr };

    ptrdiff_t nRow_{ 0 };
    ptrdiff_t nCol_{ 0 };
    ptrdiff_t length_{ 0 };
};

Matrix& operator+(const Matrix& lhs, const Matrix& rhs);
Matrix& operator-(const Matrix& lhs, const Matrix& rhs);
Matrix& operator*(const Matrix& lhs, const Matrix& rhs);

#endif // !MATRIX_H

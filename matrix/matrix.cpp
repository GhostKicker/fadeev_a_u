#include "matrix.h"
#include <stdexcept>
#include <cmath>

ptrdiff_t& Matrix::length() {
    return length_;
}

ptrdiff_t& Matrix::colNum() {
    return nCol_;
}

ptrdiff_t& Matrix::rowNum() {
    return nRow_;
}

Matrix::Matrix(const ptrdiff_t& nRow, const ptrdiff_t& nCol) {
    if ((nRow < 0)||(nCol < 0)) {
        throw (invalid_argument("You cannot simply set array size to negative!"));
    }

    nRow_ = nRow;
    nCol_ = nCol;
    length_ = nCol * nRow;
    if ((nRow_ != 0) && (nCol_ != 0)) {
        ppData_ = new double*[nRow_];
        for (ptrdiff_t i = 0; i < nRow_; i++) {
            ppData_[i] = new double[nCol_];
        }
    }
}


Matrix::~Matrix()
{
    for (int i = 0; i < nRow_; i++) {
        delete[] ppData_[i];
        ppData_[i] = nullptr;
    }
   delete[] ppData_;
   ppData_ = nullptr;
}

double& Matrix::operator()(const ptrdiff_t i, const ptrdiff_t j) {
    if (i >= nRow_) {
        throw (out_of_range("Index is out of range!"));
    }
    if (j >= nCol_) {
        throw (out_of_range("Index is out of range!"));
    }
    return *(*(ppData_ + i) + j);
}

const double& Matrix::operator()(const ptrdiff_t i, const ptrdiff_t j) const {
    if (i >= nRow_) {
        throw (out_of_range("Index is out of range!"));
    }
    if (j >= nCol_) {
        throw (out_of_range("Index is out of range!"));
    }
    return *(*(ppData_ + i) + j);
}

Matrix::Matrix(const Matrix& m) 
    :nRow_ (m.nRow_)
    ,nCol_ (m.nCol_)
    ,length_ (m.length_)
{
    ppData_ = new double*[nRow_];
    for (ptrdiff_t i = 0; i < nRow_; i++)
    {
        ppData_[i] = new double[nCol_];
    }
    for (ptrdiff_t i = 0; i < nRow_; i++)
    {
        for (ptrdiff_t j = 0; j < nCol_; j++)
        {
            *(*(ppData_ + i) + j) = *(*(m.ppData_ + i) + j);
        }
    }
}

void Matrix::swapWith(Matrix& m) {
    swap(nRow_, m.nRow_);
    swap(nCol_, m.nCol_);
    swap(length_, m.length_);
    swap(ppData_, m.ppData_);
}

Matrix& Matrix::operator=(const Matrix& obj) {
    if (this != &obj) {
        this->swapWith(Matrix(obj));
    }
    return *this;
}

Matrix& Matrix::operator+=(const Matrix& m) {
    if ((nCol_ != m.nCol_) || (nRow_ != m.nRow_)) {
        throw (invalid_argument("You can't plus matrixes with different sizes!"));
    }
    for (ptrdiff_t i = 0; i < nRow_; i++)
    {
        for (ptrdiff_t j = 0; j < nCol_; j++)
        {
            *(*(ppData_ + i) + j) += *(*(m.ppData_ + i) + j);
        }
    }
    return *this;
}

Matrix& Matrix::operator-=(const Matrix& m) {
    if ((nCol_ != m.nCol_) || (nRow_ != m.nRow_)) {
        throw (invalid_argument("You can't plus matrixes with different sizes!"));
    }
    for (ptrdiff_t i = 0; i < nRow_; i++)
    {
        for (ptrdiff_t j = 0; j < nCol_; j++)
        {
            *(*(ppData_ + i) + j) -= *(*(m.ppData_ + i) + j);
        }
    }
    return *this;
}

Matrix& Matrix::operator*=(const double& rhs) {
    for (ptrdiff_t i = 0; i < nRow_; i++)
    {
        for (ptrdiff_t j = 0; j < nCol_; j++)
        {
            *(*(ppData_ + i) + j) *= rhs;
        }
    }
    return *this;
}

Matrix operator+(const Matrix& lhs, const Matrix& rhs) {
    Matrix m(lhs);
    return m += rhs;
}

Matrix operator-(const Matrix& lhs, const Matrix& rhs) {
    Matrix m(lhs);
    return m -= rhs;
}

Matrix operator*(const Matrix& lhs, const double& rhs) {
    Matrix m(lhs);
    return m *= rhs;
}

Matrix operator*(const double& lhs, const Matrix& rhs) {
    Matrix m(rhs);
    return (m *= lhs);
}

double eps = 0.000001;
bool Matrix::operator==(const Matrix& rhs) {
    if (nRow_ != rhs.nRow_) return false;
    if (nCol_ != rhs.nCol_) return false;
    for (ptrdiff_t i = 0; i < nRow_; i++)
    {
        for (ptrdiff_t j = 0; j < nCol_; j++)
        {
            double tmp = *(*(ppData_ + i) + j) - *(*(rhs.ppData_ + i) + j);
            if (abs(tmp) > eps) return false;
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix& rhs) {
    return !(this->operator==(rhs));
}

Matrix& Matrix::operator*=(const Matrix& m) {
    if (nCol_ != m.nRow_) {
        throw (invalid_argument("You can't multiply 2 matrixes if first's nCol not equals second's nRow!"));
    }
    Matrix result(nRow_, m.nCol_);
    Matrix copy(*this);
    for (ptrdiff_t i = 0; i < result.nRow_; i++)
    {
        for (ptrdiff_t j = 0; j < result.nCol_; j++)
        {
            double tmpres = 0;
            for (ptrdiff_t k = 0; k < nCol_; k++)
            {
                tmpres += copy(i, k) * m(k, j);
            }
            result(i, j) = tmpres;
        }
    }
    this->swapWith(result);
    return *this;
}

Matrix operator*(const Matrix& lhs, const Matrix& rhs) {
    return Matrix(lhs) *= rhs;
}
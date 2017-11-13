#include "matrix.h"
#include <stdexcept>
Matrix::Matrix(const ptrdiff_t& nRow, const ptrdiff_t& nCol) {
    if ((nRow < 0)||(nCol < 0)) {
        throw (invalid_argument("You cannot simply set array size to negative!"));
    }

    nRow_ = nRow;
    nCol_ = nCol;
    length_ = nCol * nRow;
    if ((nRow_ != 0) && (nCol_ != 0)) {
        ppData_ = (new double*[nRow_]);
        for (ptrdiff_t i = 0; i < nRow_; i++)
        {
            ppData_[i] = (new double[nCol_]);
        }
    }
}

ptrdiff_t& Matrix::length() {
    return length_;
}

ptrdiff_t& Matrix::colNum() {
    return nCol_;
}

ptrdiff_t& Matrix::rowNum() {
    return nRow_;
}

Matrix::~Matrix() {
    //при наличии этой части программа завершается с ошибкой, не могу понять почему
    /*
    for (int i = 0; i < nCol_; i++)
    {
        delete[] ppData_[i];
        ppData_[i] = nullptr;
        
    }
    */
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
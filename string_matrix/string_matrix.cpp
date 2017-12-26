#include "string_matrix.h"

#include <stdexcept>

String_Matrix::String_Matrix (const ptrdiff_t& l, const ptrdiff_t& w)
{
    if (l < 0 || w < 0) {
        throw (std::invalid_argument("negative size"));
    }

    pArray_ = new std::string[l*w];
}

String_Matrix::~String_Matrix()
{
    delete[] pArray_;
}

String_Matrix::String_Matrix(const String_Matrix& m) 
{

}

String_Matrix& String_Matrix::operator=(const String_Matrix& m) 
{
    String_Matrix tmp(length_, weigth_);
    tmp.length_ = m.length_;
    tmp.weigth_ = m.weigth_;
    tmp.pArray_ = new std::string[tmp.length_*tmp.weigth_];
    for (ptrdiff_t i = 0; i < *(tmp.pArray_)->size(); i++)
    {

    }
}
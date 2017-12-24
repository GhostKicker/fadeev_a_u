#include "array.h"
#include <stdexcept>
#include <iostream>

Array::~Array(){
    delete[] pData_;
    pData_ = nullptr;
}

Array::Array(const int& sz) 
{
    if (sz < 0) {
        throw (invalid_argument("You cannot simply set array size to negative!"));
    }
    physSize_ = sz;
    logicSize_ = sz;
    if (sz != 0) {
        pData_ = (new int[logicSize_]);
    }



}

Array::Array(const Array& arr)
    : physSize_ (arr.physSize_)
    , logicSize_(arr.logicSize_)
{
    pData_ = new int[physSize_];
    for (int i = 0; i < logicSize_; i++)
    {
        *(pData_ + i) = *(arr.pData_ + i);
    }
}

int& Array::operator[](const ptrdiff_t i) {
    if (i >= logicSize_) {
        throw (out_of_range ("Index is out of range!"));
    }
    return *(pData_ + i);
}

const int& Array::operator[](const ptrdiff_t i) const 
{
    if (i >= logicSize_) {
        throw (out_of_range("Index is out of range!"));
    }
    return *(pData_ + i);

};

ptrdiff_t Array::size() const
{
    return this->logicSize_;
}

ptrdiff_t Array::capacity() const
{
    return physSize_;
}

Array& Array::operator=(const Array& obj) {
    if (this != &obj) {
        this->swapWith(Array(obj));
    }
    return *this;
}

void Array::swapWith(Array& rhs) {
    swap(physSize_, rhs.physSize_);
    swap(logicSize_, rhs.logicSize_);
    swap(pData_, rhs.pData_);
}


void Array::resize(const ptrdiff_t& newCap) {
    if (newCap < 0) {
        throw (invalid_argument("You cannot simply set new array capacity to negative!"));
    }
    Array tmp(newCap);
    tmp.logicSize_ = newCap < this->logicSize_ ? newCap : this->logicSize_;
    for (int i = 0; i < tmp.logicSize_; i++)
    {
        *(tmp.pData_ + i) = *(pData_ + i);
    }
    if (logicSize_ == 0) { pData_ = nullptr; }
    this->swapWith(tmp);
};

void Array::insert(ptrdiff_t i, int data) {
    if (i < 0) {
        throw (invalid_argument("You cannot simply insert into element with negative index!"));
    }
    if (i >= logicSize_) {
        throw (out_of_range("You cannot simply insert into element with index that is more than array size!"));
    }
    if (logicSize_ = physSize_) {
        this->resize(physSize_ + 1);
    }
    logicSize_++;
    for (int index = i+1; index < logicSize_; index++)
    {
        *(pData_ + index) = *(pData_ + index - 1);
    }
    *(pData_ + i) = data;
    //return *this;
}

void Array::erase(ptrdiff_t i) {
    if (logicSize_ == 0) {
        throw (length_error("You cannot erase from empty array!"));
    }
    if (i < 0) {
        throw (invalid_argument("You cannot simply erase negative element!"));
    }
    if (i >= logicSize_) {
        throw (out_of_range("You cannot simply erase element with index that is more than array size!"));
    }
    for (int index = i; index < logicSize_ - 1; index++)
    {
        *(pData_ + index) = *(pData_ + index + 1);
    }
    logicSize_--;
    if (logicSize_ == 0) { pData_ = nullptr; }
    //return *this;
}

void Array::push_back(const int num) {
    if (logicSize_ == physSize_) { this->resize(physSize_ + 1); }
    logicSize_++;
    this->insert(logicSize_ - 1, num);
    if (logicSize_ == physSize_) { this->resize(physSize_ - 1); }
    //return *this;
}

void Array::pop_back() {
    this->erase(logicSize_ - 1);
    //return *this;
}

Array::Array()
    :physSize_{ 0 }
    , logicSize_{ 0 }
    , pData_{ nullptr }
{
}
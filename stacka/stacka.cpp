#include "stacka.h"
#include <algorithm>
#include <stdexcept>
using namespace std;


StackA::~StackA() {
    delete[] pArray_;
    pArray_ = nullptr;
}

StackA::StackA(const ptrdiff_t& size) {
    pArray_ = new int[size];
    physSize_ = size;
}

void StackA::resize(const int& size) {
    if (size == physSize_) return;

    logicSize_ = min(logicSize_, size);
    physSize_ = size;
    int* pNew = new int[size];

    for (ptrdiff_t i = 0; i < logicSize_; i++)
    {
        *(pNew + i) = *(pArray_ + i);
    }
    swap(pNew, pArray_);
}

void StackA::push(const int& v) {
    if (physSize_ == logicSize_) resize(physSize_ + 1);

    *(pArray_ + logicSize_) = v;
    logicSize_++;

}


const ptrdiff_t& StackA::size() {
    return logicSize_;
}

const ptrdiff_t& StackA::capacity() {
    return physSize_;
}

void StackA::pop() {
    if (logicSize_) logicSize_--;
}

int& StackA::top() {
    if (logicSize_ == 0) {
        throw (out_of_range("size of stack is 0"));
    }
    return *(pArray_ + logicSize_ - 1);
}

bool StackA::isEmpty() {
    return (!logicSize_);
}

void StackA::clear() {
    logicSize_ = 0;
}

StackA& StackA::operator=(const StackA& st) {
    StackA tmp(st.physSize_);
    tmp.logicSize_ = st.logicSize_;
    for (ptrdiff_t i = 0; i < st.logicSize_; i++)
    {
        *(tmp.pArray_ + i) = *(st.pArray_ + i);
    }
    swap(this->pArray_, tmp.pArray_);
    swap(this->logicSize_, tmp.logicSize_);
    swap(this->physSize_, tmp.physSize_);
    return *this;
}

StackA::StackA(const StackA& st) {
    *this = st;
}
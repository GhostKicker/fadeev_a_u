#include "queuea.h"
#include <algorithm>
using namespace std;

QueueA::~QueueA() {
    delete[] pArray_;
}

QueueA::QueueA(const ptrdiff_t& size) {
    if (size != capacity) {
        pArray_ = new int[size];
        capacity = size;
    }
}

void QueueA::clear() {
    size = 0;
    indexHead = 0;
    indexTail = 0;
}

void QueueA::push(const int& v) {
    if (size == capacity) {
        resize(capacity + 1);
    }
    if (indexTail == capacity - 1) {
        indexTail = 0;
        *pArray_ = v;
        size++;
    }
    else {
        indexTail++;
        *(pArray_ + indexTail) = v;
        size++;
    }
}

void QueueA::resize(const ptrdiff_t& size) {
    QueueA tmp;
    tmp.pArray_ = new int[size];

    if (this->size != 0) {
        if (indexHead <= indexTail) {
            for (ptrdiff_t i = indexHead; i < indexHead + size; i++)
            {
                *(tmp.pArray_ + i) = *(this->pArray_ + i);
            }
        }
        else {
            for (ptrdiff_t i = indexHead; i < capacity; i++)
            {

            }
        }
    }

    swap(this->pArray_, tmp.pArray_);
    swap(this->indexHead, tmp.indexHead);
    swap(this->indexTail, tmp.indexTail);
}

const int& QueueA::top() {
    return *(pArray_ + indexHead);
}

const bool QueueA::isEmpty() const {
    return !(bool)(this->size);
}
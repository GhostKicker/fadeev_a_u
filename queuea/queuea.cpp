#include "queuea.h"

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
#include "priorityqueue.h"
#include <stdexcept>
using namespace std;

bool PriorityQueueL::isEmpty() const {
    return pHead_ == nullptr;
}

void PriorityQueueL::pop() {
    Node* pDel = pHead_;
    pHead_ = pHead_->pNext_;
    delete pDel;
}

const int& PriorityQueueL::top() const {
    if (isEmpty()) throw(runtime_error("stack is empty!"));
    return pHead_->data_;
}

void PriorityQueueL::push(const int& d) {
    if (!isEmpty()) {
        if (pHead_->data_ < d) {
            Node* pTmp = pHead_->pNext_;
            pHead_ = new Node(pHead_->pNext_, d);
        }
        else {
            Node* pCycle = pHead_;
            while (pCycle->pNext_ != nullptr && pCycle->pNext_->data_ >= d) {
                pCycle = pCycle->pNext_;
            }
            Node* pTmp = pCycle->pNext_;
            pCycle->pNext_ = new Node(pTmp, d);
        }
    }
    else {
        pHead_ = new Node(nullptr, d);
        pTail_ = pHead_;
    }
}

PriorityQueueL::~PriorityQueueL() {
    while (!isEmpty()) {
        pop();
    }
    pHead_ = nullptr;
    pTail_ = nullptr;
}
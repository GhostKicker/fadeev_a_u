#include "priorityqueuel.h"
#include <stdexcept>
#include <sstream>
#include <iostream>
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
            pHead_ = new Node(pHead_, d);
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
    }
}

PriorityQueueL::~PriorityQueueL() {
    while (!isEmpty()) {
        pop();
    }
    pHead_ = nullptr;
}

void PriorityQueueL::clear() {
    while (!isEmpty()) {
        pop();
    }
    pHead_ = nullptr;
}


PriorityQueueL::PriorityQueueL(const PriorityQueueL& pql) {
    PriorityQueueL q;
    Node* current = pql.pHead_;
    if (!pql.isEmpty()) {
        q.push(current->data_);
        while (current->pNext_ != nullptr) {
            current = current->pNext_;
            q.push(current->data_);
        }
    }
    swap(this->pHead_, q.pHead_);
}

PriorityQueueL& PriorityQueueL::operator=(const PriorityQueueL& rhs) { //finally, done!
    if (rhs.isEmpty()) {
        clear();
    }
    else {
        Node* pRhs = rhs.pHead_;
        if (this->isEmpty()) {
            pHead_ = new Node(nullptr, pRhs->data_);
            Node* pThis = this->pHead_;
            while (pRhs->pNext_ != nullptr) {
                pThis->pNext_ = new Node(nullptr, pRhs->pNext_->data_);
                pThis = pThis->pNext_;
                pRhs = pRhs->pNext_;
            }
        }
        else {
            Node* pThis = this->pHead_;
            pThis->data_ = pRhs->data_;
            while (pThis->pNext_ != nullptr && pRhs->pNext_ != nullptr) {
                pThis->pNext_->data_ = pRhs->pNext_->data_;
                pThis = pThis->pNext_;
                pRhs = pRhs->pNext_;
            }

            while (pRhs->pNext_ != nullptr) {
                pThis->pNext_ = new Node (nullptr, pRhs->pNext_->data_);
                pThis = pThis->pNext_;
                pRhs = pRhs->pNext_;
            }
            Node* tmp = pThis;
            pThis = pThis->pNext_;
            pRhs = pRhs->pNext_;
            tmp->pNext_ = nullptr;
            while (pThis != nullptr) {
                Node* tmp = pThis;
                pThis = pThis->pNext_;
                delete tmp;
            }
        }

    }
    return *this;
}
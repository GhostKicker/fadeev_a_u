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
            //if (pTmp == nullptr) pTail_ = pCycle->pNext_;
        }
    }
    else {
        pHead_ = new Node(nullptr, d);
        //pTail_ = pHead_;
    }
}

PriorityQueueL::~PriorityQueueL() {
    while (!isEmpty()) {
        pop();
    }
    pHead_ = nullptr;
    //pTail_ = nullptr;
}

void PriorityQueueL::clear() {
    while (!isEmpty()) {
        pop();
    }
    pHead_ = nullptr;
    //pTail_ = nullptr;
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
    //swap(this->pTail_, q.pTail_);
}

PriorityQueueL& PriorityQueueL::operator=(const PriorityQueueL& rhs) {
    if (rhs.isEmpty()) this->clear();
    if (!rhs.isEmpty()) {
        if (this->isEmpty()) { //если изначальный экземпляр пуст, то просто копируем
            PriorityQueueL tmp;
            Node* pCopyTmp = nullptr;
            Node* pCopyRhs = rhs.pHead_;
            if (rhs.pHead_ != nullptr) {
                tmp.pHead_ = new Node(nullptr, rhs.pHead_->data_);
                pCopyTmp = tmp.pHead_;
                pCopyRhs = pCopyRhs->pNext_;
                while (pCopyRhs != nullptr)
                {
                    pCopyTmp->pNext_ = new Node(nullptr, pCopyRhs->data_);
                    pCopyRhs = pCopyRhs->pNext_;
                    pCopyTmp = pCopyTmp->pNext_;
                }
            }
            swap(tmp.pHead_, pHead_);
            //swap(tmp.pTail_, pTail_);
        }
        else {
            Node* currentThis = pHead_;
            Node* currentRhs = rhs.pHead_;
            currentThis->data_ = currentRhs->data_;
            while (currentThis->pNext_ != nullptr && currentRhs->pNext_ != nullptr) {  //копируем до тех пор, пока не закончится одна из очередей
                currentThis = currentThis->pNext_;
                currentRhs = currentRhs->pNext_;
                currentThis->data_ = currentRhs->data_;
            }
            if (currentThis->pNext_ == nullptr) { // если изначальная очередь закончилась
                while (currentRhs->pNext_ != nullptr) {
                    currentThis->pNext_ = new Node(nullptr, currentRhs->pNext_->data_);
                    //pTail_ = currentThis; //к концу pTail_ должен будет указывать на конечный элемент
                    currentThis = currentThis->pNext_;
                    currentRhs = currentRhs->pNext_;
                    
                }
            }

            while (currentThis->pNext_ != nullptr) {
                Node* pTmp = currentThis;
                currentThis = currentThis->pNext_;
                delete pTmp;
            }
        }
    }
    return *this;
}
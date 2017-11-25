#include "stackl.h"
#include <stdexcept>
using namespace std;
void StackL::push(const int& data) {
    pHead_ = new Node(pHead_, data);
}

int& StackL::top() {
    if (isEmpty()) throw(runtime_error("stack is empty!"));
    return pHead_->data_;
}

const int& StackL::top() const {
    if (isEmpty()) throw(runtime_error("stack is empty!"));
    return pHead_->data_;
}

void StackL::pop() {
    Node* pDel = pHead_;
    pHead_ = pHead_->pNext_;
    delete pDel;
}

bool StackL::isEmpty() const {
    return nullptr == pHead_;
}

StackL::~StackL() {
    while (!isEmpty()) {
        pop();
    }
}

void StackL::clear() {
    while (!isEmpty()) {
        pop();
    }
}

StackL::StackL(const StackL& st) { //wrong, will be rewritten
    pHead_ = nullptr;
    if (!st.isEmpty()) {
        pHead_ = new Node(nullptr, st.pHead_->data_);
        Node* current = pHead_;
        Node* currentst = st.pHead_;
        do {
            currentst = currentst->pNext_;
            current->pNext_ = new Node(nullptr, currentst->data_);
            current = current->pNext_;
        } while (!(nullptr == currentst->pNext_));
    }
}

StackL& StackL::operator=(const StackL& obj) {
    if (this != &obj) {
        StackL tmpst(obj);
        Node* tmp = tmpst.pHead_;
        tmpst.pHead_ = pHead_;
        pHead_ = tmp;

    }
    return *this;
}
#ifndef STACKA_H
#define STACKA_H

#include <cstddef>

class StackA {
public:
    StackA() = default;
    StackA(const StackA& st);
    StackA(const ptrdiff_t& size);
    ~StackA();

    StackA& operator=(const StackA& st);
    const ptrdiff_t& size();
    const ptrdiff_t& capacity();
    void push(const int& v);
    void pop();
    int& top();
    void clear();
    void resize(const int& size);
    bool isEmpty();

private:

    int* pArray_ = nullptr;
    ptrdiff_t physSize_ = 0;
    ptrdiff_t logicSize_ = 0;




};


#endif // !STACKA_H

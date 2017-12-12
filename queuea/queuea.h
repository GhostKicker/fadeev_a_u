#ifndef QUEUEA_H
#define QUEUEA_H

#include <cstddef>

class QueueA 
{
public:

    QueueA() = default;
    QueueA(const ptrdiff_t& size);
    QueueA(const QueueA& q);
    ~QueueA();

    QueueA& operator=(QueueA& q);

    const int& top();
    void push(const int& v);
    void pop();
    void clear();
    bool isEmpty() const;

    void resize(ptrdiff_t& size);

private:

    int* pArray_ = nullptr;
    ptrdiff_t size = 0;
    ptrdiff_t capacity = 0;
    ptrdiff_t indexHead = 0;
    ptrdiff_t indexTail = 0;

};



#endif // !QUEUEA_H

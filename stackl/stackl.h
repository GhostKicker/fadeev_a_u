#ifndef STACKL_H
#define STACKL_H
#include <cstddef>

class StackL 
{
public:

    StackL() = default;
    StackL(const StackL& st);
    ~StackL();

    StackL& operator=(const StackL& rhs);

    void clear();
    void push(const int& data);
    void pop();
    int& top();
    const int& top() const;
    bool isEmpty() const;

private:
    struct Node 
    {
        Node* pNext_ = nullptr;
        int data_ = int(0);

        Node(Node* pNode, const int& v) 
            :pNext_(pNode)
            ,data_(v)
        {
        }
    };
    Node* pHead_ = nullptr;
    
};

#endif 
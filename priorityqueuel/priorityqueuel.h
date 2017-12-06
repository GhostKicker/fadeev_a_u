#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

class PriorityQueueL {
public:
    PriorityQueueL() = default;
    PriorityQueueL(const PriorityQueueL& pql);
    ~PriorityQueueL();

    PriorityQueueL& operator=(const PriorityQueueL& rhs);

    void clear();
    void push(const int& data);
    void pop();
    const int& top() const;
    bool isEmpty() const;

private:
    struct Node 
    {
        Node* pNext_ = nullptr;
        int data_ = int(0);

        Node(Node* pNode, const int& d) 
            :pNext_(pNode)
            ,data_(d)
        {
        }

    };
    Node* pHead_ = nullptr;
};



#endif // !PRIORITYQUEUE_H

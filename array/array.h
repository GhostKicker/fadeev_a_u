#ifndef ARRAY_H
#define ARRAY_H

#include <cstddef>
using namespace std;

class Array {
    //erase(i), push_back, pop_back
public:
    Array() = default;
    Array(const Array& ar);
    Array(const int& size);
    ~Array();

    void swapWith(Array& rhs);
    void resize(const ptrdiff_t& newCap);

    ptrdiff_t& size();
    ptrdiff_t& capacity();
    void insert(ptrdiff_t i, int data);
    void erase(ptrdiff_t i);
    void push_back(const int num);
    void pop_back();
    int& operator[](const ptrdiff_t i);
    const int& operator[](const ptrdiff_t i) const;

    Array& operator=(const Array& obj);

private:
    ptrdiff_t physSize_{ 0 };
    ptrdiff_t logicSize_{ 0 };
    int* pData_{ nullptr };

};





#endif // !ARRAY_H

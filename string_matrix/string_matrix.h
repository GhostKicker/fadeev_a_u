#ifndef STRING_MATRIX_H
#define STRING_MATRIX_H

#include <cstddef>
#include <string>

class String_Matrix 
{
public:
    String_Matrix() = default;
    String_Matrix(const ptrdiff_t& l, const ptrdiff_t& w);
    String_Matrix(const String_Matrix& m);
    ~String_Matrix();

    String_Matrix& operator=(const String_Matrix& m);

private:
    ptrdiff_t length_;
    ptrdiff_t weigth_;
    std::string* pArray_;
};




#endif
#include "matrix.h"
#include <iostream>

void matrixOut(Matrix& m) {
    for (size_t i = 0; i < m.rowNum(); i++)
    {
        for (size_t j = 0; j < m.colNum(); j++)
        {
            cout << m(i, j) << " ";
        }
        cout << endl;
    }
}

int main() {
    Matrix m1();
    Matrix m2(4, 3);
    //cout << "here" << endl;
    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            m2(i, j) = 3*i + j;
        }
    }
    matrixOut(m2);
    cout << "Row number = " << m2.rowNum() << endl;
    cout << "Col number = " << m2.colNum() << endl;
    m2.~Matrix();

    int n;
    cin >> n;
    return 0;
}
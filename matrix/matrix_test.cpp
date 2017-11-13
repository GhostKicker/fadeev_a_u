#include "matrix.h"
#include <iostream>

void matrixOut(Matrix& m) {
    for (ptrdiff_t i = 0; i < m.rowNum(); i++)
    {
        for (ptrdiff_t j = 0; j < m.colNum(); j++)
        {
            cout << m(i, j) << " ";
        }
        cout << endl;
    }
    cout << "Row number = " << m.rowNum() << endl;
    cout << "Col number = " << m.colNum() << endl;
    cout << "Length = " << m.length() << endl;
}
void matrixIn(Matrix& m) {
    for (ptrdiff_t i = 0; i < m.rowNum(); i++)
    {
        for (ptrdiff_t j = 0; j < m.colNum(); j++)
        {
            m(i, j) = m.rowNum()*i + j;
        }
    }

}


int main() {
    Matrix m1();
    Matrix m2(3, 3);
    Matrix m6(4, 3);
    Matrix m7(3, 4);
    matrixIn(m2);
    matrixIn(m6);
    matrixIn(m7);
    //cout << "here" << endl;
    cout << "---------m2---------" << endl;
    matrixOut(m2);
    cout << "-------m3(m2)-------" << endl;
    Matrix m3(m2);
    matrixOut(m3);
    cout << "--------m4=m2-------" << endl;
    Matrix m4;
    m4 = m2;
    matrixOut(m4);
    cout << "-------m5+=m4-------" << endl;
    Matrix m5(m4);
    m5 += m4;
    matrixOut(m5);
    cout << "-------m6+=m4-------" << endl;
    try {
        m6 += m4;
    }
    catch (invalid_argument e) {
        cout << "I tried to summ matrixes with different sizes but I couldn't" << endl;
    }
    cout << "-------m4-=m2-------" << endl;
    m4 -= m2;
    matrixOut(m4);
    cout << "-------m6-=m4-------" << endl;
    try {
        m6 -= m4;
    }
    catch (invalid_argument e) {
        cout << "I tried to deduct matrixes with different sizes but I couldn't" << endl;
    }

    m2.~Matrix();

    int n;
    cin >> n;
    return 0;
}
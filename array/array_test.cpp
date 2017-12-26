#include "array.h"
#include <iostream>
#include <sstream>
#include <cstddef>


void writeArray(Array& arr, string name) {
    cout << "array " << name << " ==> ";
    for (int i = 0; i < arr.size(); i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    Array abc();
    //writeArray(abc, "abc");
    Array b(5);
    b[0] = 1;
    b[1] = 2;
    b[2] = 6;
    b[3] = 2;
    b[4] = 5;
    Array c(b);
    Array d(c);
    Array e(0);

    try {
        e.erase(1234);
    }
    catch (length_error e) {
        cout << "I've tried to erase from empty array but I couldn't!" << endl;
    }

    e = c;

    try {
        b[5] = 3;
    }
    catch (out_of_range e) {
        cout << "I've tried to set element with index out of range to something but I couldn't!" << endl;
    }

    writeArray(b, "b");
    writeArray(c, "c, copy of b");
    writeArray(e, "e = c");
    e.insert(4, 1541);

    try {
        e.insert(-1, 2);
    } catch (invalid_argument e) {cout << "I've tried to insert into negative index but I couldn't!" << endl;}

    try {
        e.insert(6, 2);
    } catch (out_of_range e) {cout << "I've tried to insert into index out of range but I couldn't!" << endl;}

    writeArray(e, "e after insertion");
    try {
        e.erase(-1);
    }
    catch (invalid_argument e) {
        cout << "I've tried to erase from negative index but I couldn't!" << endl;
    }
    try {
        e.erase(1234);
    }
    catch (out_of_range e) {
        cout << "I've tried to erase index out of range but I couldn't!" << endl;
    }
    e.erase(4);
    writeArray(e, "e after erasing");
    e.resize(7);
    cout << "array e after resizing: size = " << e.size() << "; capacity = " << e.capacity() << endl;
    writeArray(e, "e");
    e.resize(3);
    writeArray(e, "e after another resizing");
    try {
        e.resize(-1);
    } catch (invalid_argument e) {cout << "I've tried to set size to negative but I couldn't!" << endl;}
    b.push_back(123);
    writeArray(b, "b");
    b.pop_back();
    writeArray(b, "b");

}
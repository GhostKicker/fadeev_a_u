#include <iostream>
#include <sstream>
#include "vec3dT.h"
using namespace std;

template<typename T>
void VOUT(Vec3dT<T>& lhs);

template <typename T>
void VoperOUT(Vec3dT<T>& lhs, const string oper, Vec3dT<T>& rhs);

int main() {
    Vec3dT<string> v4 ("a","b","c");
    Vec3dT<string> v3("b","a","c");
    Vec3dT<double> v(2.1, 2.2, 2.3);
    Vec3dT<double> v1(2.10000001, 2.2, 2.3);
    Vec3dT<double> v2();
    VoperOUT(v, "+", v1);
    VOUT(v1 + v); 
    cout << endl;
    VoperOUT(v, "-", v1);
    VOUT(v1 - v);
    cout << endl;
    VoperOUT(v, "==", v1);
    cout << (v == v1);
    cout << endl;
    VoperOUT(v, "!=", v1);
    cout << (v != v1);
    cout << endl;
    VoperOUT(v3, "==", v4);
    cout << (v3 == v4);
    cout << endl;
    VoperOUT(v3, "!=", v4);
    cout << (v3 != v4);
    cout << endl;

    int a;
    cin >> a;
	return 0;
}

template <typename T>
void VOUT(Vec3dT<T>& lhs) {
    cout << "{ " << lhs.x << "; " << lhs.y << "; " << lhs.z << " }";
}

template <typename T>
void VoperOUT(Vec3dT<T>& lhs, const string oper, Vec3dT<T>& rhs) {
    VOUT(lhs);
    cout << " " << oper << " ";
    VOUT(rhs);
    cout << " = ";
}
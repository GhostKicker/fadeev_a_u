#include <iostream>
#include <sstream>
#include "vec3dT.h"
using namespace std;

template<typename T>
void VOUT(Vec3dT<T>& lhs);

template <typename T>
void VoperOUT(Vec3dT<T>& lhs, const string oper, Vec3dT<T>& rhs);

template <typename T>
void VoperOUT(Vec3dT<T>& lhs, const string oper, double& rhs);

int main() {
    double a = 4.0;
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
    VoperOUT(v, "*", a);
    VOUT(v1 * a);
    cout << endl;
    VoperOUT(v, "/", a);
    VOUT(v1 / a);
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
    cout << "length of ";
    VOUT(v);
    cout << " is " << v.length() << endl;
    cout << "dot product of ";
    VOUT(v);
    cout << " and ";
    VOUT(v1);
    cout << " is " << dotProduct(v, v1) << endl;
    cout << "cross product of ";
    VOUT(v);
    cout << " and ";
    VOUT(v1);
    cout << " is ";
    VOUT(crossProduct(v, v1));
    cout << endl;

    //cin >> a;
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

template <typename T>
void VoperOUT(Vec3dT<T>& lhs, const string oper, double& rhs) {
    VOUT(lhs);
    cout << " " << oper << " ";
    cout << (rhs);
    cout << " = ";
}
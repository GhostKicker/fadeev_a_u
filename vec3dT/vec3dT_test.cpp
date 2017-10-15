#include <iostream>
#include "vec3dT.h"
using namespace std;

template<typename T>
void VOUT(Vec3dT<T>& lhs);

template <typename T>
void VoperVOUT(Vec3dT<T>& lhs, string oper, Vec3dT<T>& rhs);

int main() {
    Vec3dT<double> v (2.3, 3.4, 4.5);
    Vec3dT<double> v1(1.0, 2.0, 3.0);
    Vec3dT<double> v2();
    VoperVOUT(v, "+", v1);
    VOUT(v1 + v);
    //v = v + v1;
    v += v1;
    v = v - v1;
    v -= v1;
    bool a = (v == v1);
    bool b = (v != v1);
    cin >> a;
	return 0;
}

template <typename T>
void VOUT(Vec3dT<T>& lhs) {
    cout << "{ " << lhs.x << "; " << lhs.y << "; " << lhs.z << " }";
}

template <typename T>
void VoperVOUT(Vec3dT<T>& lhs, string oper, Vec3dT<T>& rhs) {
    VOUT(lhs);
    cout << " " << oper << " ";
    VOUT(rhs);
    cout << " = ";
}
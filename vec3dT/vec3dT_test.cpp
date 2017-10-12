#include <iostream>
#include "vec3dT.h"
using namespace std;



int main() {
    Vec3dT<double> v (2.3, 3.4, 4.5);
    Vec3dT<double> v1(1.0, 2.0, 3.0);
    Vec3dT<double> v2();
    v = v + v1;
    v += v1;
    v = v - v1;
    v -= v1;
    bool a = (v == v1);
    bool b = (v != v1);
	return 0;
}
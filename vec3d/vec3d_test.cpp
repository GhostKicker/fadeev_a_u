#include <iostream>
#include "vec3d.h"
using namespace std;


int main() {
    Vec3d v1(2.0, 4.0, 6.0);
    Vec3d v(3, 4, 5);
    Vec3d v7(3.0,-4.0,12.0);
    Vec3d v2 = v1;
    Vec3d v4(-2.0, 4.1, 5.1);
    Vec3d v5(-2.0, 4.100009, 5.1);
    Vec3d v6(-2.0, 4.10001, 5.1);
    Vec3d v8(2, 0, 0);
    Vec3d v9(0, 2, 0);
    cout << v4 << " == " << v5 << " <==> " << ((v4 == v5) ? "true" : "false") << endl;
    cout << v4 << " == " << v6 << " <==> " << ((v4 == v6) ? "true" : "false") << endl;
    cout << v4 << " != " << v6 << " <==> " << ((v4 != v6) ? "true" : "false") << endl;
    cout << v << " * " << 3.5 << " = " << v*3.5 << endl;
    cout << 3.5 << " * " << v << " = " << 3.5*v << endl;
    cout << v << " / " << -3.5 << " =" << v / (-3.5) << endl;
    v = v + v1;
    cout << "- " << v << " = " << (-v) << endl;
    cout << "Vector length of " << v7 << " is " << v7.length() << endl;
    cout << "Dot product of " << v1 << " and " << v7 << " is " << dotProduct(v1, v7) << endl;
    cout << "Cross product of " << v8 << " and " << v9 << " is " << crossProduct(v8, v9) << endl;

    return 0;
}
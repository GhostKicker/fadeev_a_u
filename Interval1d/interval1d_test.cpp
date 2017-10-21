#include <iostream>
#include "Interval1d.h"
using namespace std;




int main() {
    Interval1d i1();
    Interval1d i2(true, 2, 4, false);
    Interval1d i3(i2);
    Interval1d i4(true, 5, 7, false);
    Interval1d i5(false, 2, 4, false);
    cout << i2 << endl << i3 << endl;
    cout << i2.length() << endl;
    cout << i3.isIntersepting(i2) << endl;
    cout << i4 << endl << i5 << endl;
    //cout << "interseption " << i5.interseptionWith(i4);
    int qwe;
    cin >> qwe;
    return 0;
}
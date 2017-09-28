#include "complex.h"
#include <iostream>

int main()
{
	using namespace std;

	Complex z;
	Complex v;
	double h(3.5);
	cout << "{1.0 , 2.3} + {0.75 , -0.7} = " << Complex(1.0, 2.3) + Complex(0.75, -0.7) << endl;
	cout << "{1.0 , 2.3} - {0.0 , -0.7} = " << Complex(1.0, 2.3) - Complex(0.0, -0.7) << endl;
	cout << "{1.0 , 2.3} * {3.0 , 2.1} = " << Complex(1.0, 2.3) * Complex(3.0, 2.1) << endl;
	cout << "{1.0 , 2.3} / {3.1 , 1.0} = " << Complex(1.0, 2.3) + Complex(3.1, 1.0) << endl;
	cout << "Epsilon for doubles in this case is 0.00001" << endl;
	cout << "{1.0 , 1.0} == {1.000009 , 1.0} <=> " << ((Complex(1.0, 1.0) == Complex(1.000009, 1.0)) ? "true" : "false") << endl;
	cout << "{1.0 , 1.0} == {1.00001 , 1.0} <=> " << ((Complex(1.0, 1.0) == Complex(1.00001, 1.0)) ? "true" : "false") << endl;
	cout << "{1.0 , 1.0} != {1.000009 , 1.0} <=> " << ((Complex(1.0, 1.0) != Complex(1.000009, 1.0)) ? "true" : "false") << endl;
	cout << "{1.0 , 1.0} != {1.00001 , 1.0} <=> " << ((Complex(1.0, 1.0) != Complex(1.00001, 1.0)) ? "true" : "false") << endl;
	cout << "Input first complex number" << endl;
	cin >> v;
	cout << "Input second complex number" << endl;
	cin >> z;
	cout << v << " + " << z << " = " << v + z << endl;
	cout << v << " - " << z << " = " << v - z << endl;
	cout << v << " * " << z << " = " << v * z << endl;
	cout << v << " / " << z << " = " << v / z << endl;
	cout << v << " + " << h << " = " << v + h << endl;
	cout << v << " - " << h << " = " << v - h << endl;
	cout << v << " * " << h << " = " << v * h << endl;
	cout << v << " / " << h << " = " << v / h << endl;
	testParse("{8.9,9 }");
	testParse("{8.9, 9}");
	testParse("{ 8.9,9}");
	int j(0);
	cin >> j;
	return 0;
}

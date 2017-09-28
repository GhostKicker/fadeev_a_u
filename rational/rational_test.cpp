#include "rational.h"
#include <iostream>

int main()
{
	using namespace std;
	Rational a;
	Rational b;
	cout << "1/2 and 1/3" << endl;
	RationalBasicTest(cout, Rational(1, 2), Rational(1, 3));
	cout << "1/2 and -2" << endl;
	RationalBasicTest(cout, Rational(1, 2), -2);
	//cout << "-2 and 1/3" << endl;
	//RationalBasicTest(cout, -2, Rational(1, 3));
	cout << "Input first rational number" << endl;
	cin >> a;
	cout << a << endl;
	cout << "Input second rational number" << endl;
	cin >> b;
	cout << b << endl;
	Rational aa(a);
	Rational bb(b);
	cout << "nonnormalized a and b : " << aa << "  " << bb << endl;
	normalizeRationals(aa, bb);
	cout << "normalized a and b    : " << aa << "  " << bb << endl;
	RationalBasicTest(cout, a, b);
	int d;
	cin >> d;
	return 0;
}
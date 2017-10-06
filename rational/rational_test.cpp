#include "rational.h"
#include <iostream>
#include <sstream>

using namespace std;
bool testParse(const std::string str)
{
	using namespace std;
	istringstream istrm(str);
	Rational z;
	istrm >> z;
	if (istrm.good())
	{
		cout << "Read success: " << str << z << endl;
	}
	else {
		cout << "Read error  : " << str << z << endl;
	}
	return istrm.good();
}

int main()
{
	using namespace std;
	Rational a;
	Rational b;
	Rational c(3, 5);
	cout << "1/2 and 1/3" << endl;
	RationalBasicTest(cout, Rational(1, 2), Rational(1, 3));
	cout << "1/2 and -2" << endl;
	RationalBasicTest(cout, Rational(1, 2), -2);
	cout << "-1 * " << c  << " = " << -c << endl;
	//cout << "-2 and 1/3" << endl;
	//RationalBasicTest(cout, -2, Rational(1, 3));
	testParse("3/ 5");
	testParse("-3 :5");
	testParse("-3 / 2");
	cout << "Input first rational number" << endl;
	cin >> a;
	cout << a << endl;
	cout << "Input second rational number" << endl;
	cin >> b;
	cout << b << endl;
	Rational aa(a);
	Rational bb(b);
	cout << "nonnormalized a and b : " << aa << "  " << bb << endl;
	aa.normalizeWith(bb);
	cout << "normalized a and b    : " << aa << "  " << bb << endl;
	RationalBasicTest(cout, a, b);
	int d;
	cin >> d;
	return 0;
}


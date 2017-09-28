#ifndef RATIONAL_H
#define RATIONAL_H
#include <iosfwd>
struct Rational
{
	Rational() {}

	explicit Rational(const int num);
	Rational(const int num, const int denum);

	bool operator==(const Rational& rhs);
	bool operator==(const int& rhs);
	bool operator!=(const Rational& rhs);
	bool operator!=(const int& rhs);
	bool operator>(const Rational& lhs);
	bool operator<(const Rational& rhs);
	bool operator>(const int rhs);
	bool operator<(const int rhs);
	bool operator<=(const Rational rhs);
	bool operator>=(const Rational rhs);

	Rational& operator+=(const Rational& lhs);
	Rational& operator+=(const int lhs);
	Rational& operator-=(const Rational& lhs);
	Rational& operator-=(const int lhs);
	Rational& operator*=(const Rational& lhs);
	Rational& operator*=(const int lhs);
	Rational& operator/=(const Rational& lhs);
	Rational& operator/=(const int lhs);


	Rational& operator-() { return Rational(-num, denum); }

	int num{ 0 };
	int denum{ -1 };

	std::ostream& writeTo(std::ostream& ostrm) const;
	std::istream& readFrom(std::istream& istrm);
	static const char slash{ '/' };
};

void normalizeRationals(Rational& a, Rational& b);

Rational operator+ (const Rational& lhs, const  Rational& rhs);
Rational operator- (const Rational& lhs, const Rational& rhs);
Rational operator* (const Rational& lhs, const Rational& rhs);
Rational operator/ (const Rational& lhs, const Rational& rhs);

Rational operator+ (const Rational& lhs, const int& rhs);
Rational operator- (const Rational& lhs, const int& rhs);
Rational operator* (const Rational& lhs, const int& rhs);
Rational operator/ (const Rational& lhs, const int& rhs);

Rational operator+ (const int& lhs, const  Rational& rhs);
Rational operator- (const int& lhs, const Rational& rhs);
Rational operator* (const int& lhs, const Rational& rhs);
Rational operator/ (const int& lhs, const Rational& rhs);

std::ostream& operator<<(std::ostream& ostrm, const Rational& rhs);

std::istream& operator>>(std::istream& istrm, Rational& rhs);

void RationalBasicTest(std::ostream& ostrm, const Rational& lhs, const Rational& rhs);
void RationalBasicTest(std::ostream& ostrm, const int& lhs, const Rational& rhs);
void RationalBasicTest(std::ostream& ostrm, const Rational& lhs, const int& rhs);

#endif // !COMPLEX_H


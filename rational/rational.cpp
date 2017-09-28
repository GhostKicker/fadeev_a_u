#include "Rational.h"
#include <iostream>
#include <sstream>
#include <stdexcept>

int GCD(int a, int b)
{
	while (b) {
		a %= b;
		int c = a;
		a = b;
		b = c;
	}

	return a;
}

int LCD(int a, int b)
{
	return (a*b / GCD(a, b));
}



std::ostream& operator<<(std::ostream& ostrm, const Rational& rhs)
{
	return rhs.writeTo(ostrm);
}

std::istream& operator>>(std::istream& istrm, Rational& rhs)
{
	return rhs.readFrom(istrm);
}

Rational::Rational(const int nume)
	: Rational(nume, 1)
{
}

Rational::Rational(const int nume, const int denume)
	: num(nume)
	, denum(denume)
{
	
	if (0 == denum) // had (denum = 0) thing... now I understand
	{
		throw ("Denumenator hasn't be 0");
		
	}

	int g = (GCD(nume,denume));
	num /= g;
	denum /= g;
	
	if (denum < 0)
	{
		num = -num;
		denum = -denum;
	}
}

std::ostream& Rational::writeTo(std::ostream& ostrm) const
{
	ostrm << num << slash << denum;
	return ostrm;
}

std::istream& Rational::readFrom(std::istream& istrm)
{
	int numerator(0);
	char line(0);
	int denumerator(0);
	istrm >> numerator >> line >> denumerator;
	if (istrm.good())
	{
		if ((Rational::slash == line) && (denumerator > 0))
		{
			num = numerator;
			denum = denumerator;
			*this = Rational(num, denum);
		}
		else {
			istrm.setstate(std::ios_base::failbit);
		}
	}
	return istrm;
}

void normalizeRationals(Rational& a, Rational& b)
{
	int denume = LCD(a.denum, b.denum);
	int anum = a.num * (denume / a.denum);
	int bnum = b.num * (denume / b.denum);
	a.num = anum; a.denum = denume;
	b.num = bnum; b.denum = denume;
}



bool Rational::operator==(const Rational& rhs)
{
	Rational a(num, denum);
	Rational b(rhs);
	normalizeRationals(a, b);
	return ((a.num == b.num) && (a.denum == b.denum));
}
bool Rational::operator==(const int& rhs)
{
	return operator==(Rational(rhs));
};
bool Rational::operator!=(const Rational& rhs) { return !operator==(rhs); }
bool Rational::operator!=(const int& rhs) { return operator!=(Rational(rhs)); }

Rational& Rational::operator+=(const Rational& rhs)
{
	Rational rhss(rhs);
	normalizeRationals(*this, rhss);
	num = num + rhss.num;
	*this = Rational(num, denum);
	return *this;
}
Rational& Rational::operator-=(const Rational& rhs)
{
	Rational rhss(rhs);
	normalizeRationals(*this, rhss);
	num = num - rhss.num;
	*this = Rational(num, denum);
	return *this;
}

Rational& Rational::operator*=(const Rational& rhs)
{
	num *= rhs.num;
	denum *= rhs.denum;
	*this = Rational(num, denum);
	if (denum < 0)
	{
		num = -num;
		denum = -denum;
	}
	return *this;
}

Rational& Rational::operator/=(const Rational& rhs)
{
	Rational r(rhs);
	if (r < 0)
	{
		r.num = -r.num;
		r = Rational(r.denum, r.num);
		r.num = -r.num;
	}
	else {
		r = Rational(r.denum, r.num);
	}
	return (operator*=(r));
};

Rational operator+ (const Rational& lhs, const int& rhs) { return (lhs + Rational(rhs)); };
Rational operator- (const Rational& lhs, const int& rhs) { return (lhs - Rational(rhs)); };
Rational operator* (const Rational& lhs, const int& rhs) { return (lhs * Rational(rhs)); };
Rational operator/ (const Rational& lhs, const int& rhs) { return (lhs / Rational(rhs)); };

Rational operator+ (const int& lhs, const Rational& rhs) { return (Rational(lhs) + rhs); };
Rational operator- (const int& lhs, const Rational& rhs) { return (Rational(lhs) - rhs); };
Rational operator* (const int& lhs, const Rational& rhs) { return (Rational(lhs) * rhs); };
Rational operator/ (const int& lhs, const Rational& rhs) { return (Rational(lhs) / rhs); };

bool Rational::operator<=(const Rational rhs) { return (operator==(rhs) || operator<(rhs)); }
bool Rational::operator>=(const Rational rhs) { return (operator==(rhs) || operator>(rhs)); }

bool Rational::operator>(const int rhs) { return operator>(Rational(rhs)); };
bool Rational::operator<(const int rhs) { return operator<(Rational(rhs)); };

Rational& Rational::operator+=(const int lhs) { return operator+=(Rational(lhs)); }
Rational& Rational::operator-=(const int lhs) { return operator-=(Rational(lhs)); }
Rational& Rational::operator*=(const int lhs) { return operator*=(Rational(lhs)); }
Rational& Rational::operator/=(const int lhs) { return operator/=(Rational(lhs)); }

bool Rational::operator<(const Rational& rhs)
{
	Rational a(num, denum);
	Rational b(rhs);
	normalizeRationals(a, b);
	return (a.num < b.num);
}

bool Rational::operator>(const Rational& rhs)
{
	Rational a(num, denum);
	Rational b(rhs);
	normalizeRationals(a, b);
	return (a.num > b.num);
}

Rational operator+(const Rational& lhs, const Rational& rhs)
{
	Rational s(lhs);
	s += rhs;
	return s;
}

Rational operator-(const Rational& lhs, const Rational& rhs)
{
	Rational s(lhs);
	s -= rhs;
	return s;
}

Rational operator*(const Rational& lhs, const Rational& rhs)
{
	Rational s(lhs);
	s *= rhs;
	return s;
}

Rational operator/(const Rational& lhs, const Rational& rhs)
{
	Rational s(lhs);
	s /= rhs;
	return s;
}

void RationalBasicTest(std::ostream& ostrm, const Rational& a, const Rational& b) 
{
	Rational h(a);
	ostrm << a << " + " << b << " = " << (a + b) << std::endl;
	ostrm << a << " - " << b << " = " << (a - b) << std::endl;
	ostrm << a << " * " << b << " = " << (a * b) << std::endl;
	ostrm << a << " / " << b << " = " << (a / b) << std::endl;
	ostrm << a << " < " << b << " <=> " << ((h < b) ? "true" : "false") << std::endl;
	ostrm << a << " > " << b << " <=> " << ((h > b) ? "true" : "false") << std::endl;
	ostrm << a << " == " << b << " <=> " << ((h == b) ? "true" : "false") << std::endl;
	ostrm << a << " != " << b << " <=> " << ((h != b) ? "true" : "false") << std::endl;
	ostrm << "-------------------" << std::endl;
};
/*
void RationalBasicTest(std::ostream& ostrm, const int& a, const Rational& b)
{
	int h(a);
	ostrm << a << " + " << b << " = " << (a + b) << std::endl;
	ostrm << a << " - " << b << " = " << (a - b) << std::endl;
	ostrm << a << " * " << b << " = " << (a * b) << std::endl;
	ostrm << a << " / " << b << " = " << (a / b) << std::endl;
	ostrm << a << " < " << b << " <=> " << ((h < b) ? "true" : "false") << std::endl;
	ostrm << a << " > " << b << " <=> " << ((h > b) ? "true" : "false") << std::endl;
	ostrm << a << " == " << b << " <=> " << ((h == b) ? "true" : "false") << std::endl;
	ostrm << a << " != " << b << " <=> " << ((h != b) ? "true" : "false") << std::endl;
	ostrm << "-------------------" << std::endl;
};*/
void RationalBasicTest(std::ostream& ostrm, const Rational& a, const int& b)
{
	Rational h(a);
	ostrm << a << " + " << b << " = " << (a + b) << std::endl;
	ostrm << a << " - " << b << " = " << (a - b) << std::endl;
	ostrm << a << " * " << b << " = " << (a * b) << std::endl;
	ostrm << a << " / " << b << " = " << (a / b) << std::endl;
	ostrm << a << " < " << b << " <=> " << ((h < b) ? "true" : "false") << std::endl;
	ostrm << a << " > " << b << " <=> " << ((h > b) ? "true" : "false") << std::endl;
	ostrm << a << " == " << b << " <=> " << ((h == b) ? "true" : "false") << std::endl;
	ostrm << a << " != " << b << " <=> " << ((h != b) ? "true" : "false") << std::endl;
	ostrm << "-------------------" << std::endl;
};
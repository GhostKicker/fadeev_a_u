#include <iostream>
#include <sstream>
#include "complex.h"



Complex operator+(const Complex& lhs, const double rhs) { return operator+(lhs, Complex(rhs)); };
Complex operator-(const Complex& lhs, const double rhs) { return operator-(lhs, Complex(rhs)); };
Complex operator*(const Complex& lhs, const double rhs) { return operator*(lhs, Complex(rhs)); };
Complex operator/(const Complex& lhs, const double rhs) { return operator/(lhs, Complex(rhs)); };

std::ostream& operator<<(std::ostream& ostrm, const Complex& rhs)
{
	return rhs.writeTo(ostrm);
}

std::istream& operator>>(std::istream& istrm, Complex& rhs)
{
	return rhs.readFrom(istrm);
}

bool testParse(const std::string& str)
{
	using namespace std;
	istringstream istrm(str);
	Complex z;
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


Complex::Complex(const double real)
	: Complex(real, 0.0)
{
}

Complex::Complex(const double real, const double imagenary)
	: re(real)
	, im(imagenary)
{
}


const double Eps{ 0.00001 };

bool Complex::operator==(const Complex& rhs) const 
{
	bool a = (abs(re - rhs.re) < Eps);
	bool b = (abs(im - rhs.im) < Eps);
	if (a && b) 
	{
		return true;
	}
	else {
		return false;
	}
};

bool Complex::operator!=(const Complex& rhs) const { return !operator==(rhs); }

Complex& Complex::operator+=(const Complex& rhs)
{
	re += rhs.re;
	im += rhs.im;
	return *this;
}

Complex& Complex::operator-=(const Complex& rhs)
{
	re -= rhs.re;
	im -= rhs.im;
	return *this;
}

Complex operator+(const Complex& lhs, const Complex& rhs)
{
	Complex sum(lhs);
	sum += rhs;
	return sum;
}

Complex operator-(const Complex& lhs, const Complex& rhs)
{
	Complex dif(lhs);
	dif -= rhs;
	return dif;
}

Complex operator*(const Complex& lhs, const Complex& rhs)
{
	Complex com(lhs);
	com *= rhs;
	return com;
}

Complex operator/(const Complex& lhs, const Complex& rhs)
{
	Complex quo(lhs);
	quo /= rhs;
	return quo;
}

Complex& Complex::operator*=(const double rhs)
{
	re *= rhs;
	im *= rhs;
	return *this;
}

Complex& Complex::operator/=(const double rhs)
{
	re /= rhs;
	im /= rhs;
	return *this;
}

Complex& Complex::operator*=(const Complex& rhs)
{
	re = (re * rhs.re - im * rhs.im);
	im = (re * rhs.im + im * rhs.re);
	return *this;
}

Complex& Complex::operator/=(const Complex& rhs)
{
	re = (re * rhs.re + im * rhs.im) / (rhs.re * rhs.re + rhs.im * rhs.im);
	im = (im * rhs.re - re * rhs.im) / (rhs.re * rhs.re + rhs.im * rhs.im);
	return *this;
}

Complex& Complex::operator-()
{
	re = -re;
	im = -im;
	return *this;
}

std::ostream& Complex::writeTo(std::ostream& ostrm) const
{
	ostrm << leftBrace << re << separator << im << rightBrace;
	return ostrm;
}

std::istream& Complex::readFrom(std::istream& istrm)
{
	char leftBrace(0);
	double real(0.0);
	char comma(0);
	double imaganary(0.0);
	char rightBrace(0);
	istrm >> leftBrace >> real >> comma >> imaganary >> rightBrace;
	if (istrm.good())
	{
		if ((Complex::leftBrace == leftBrace) && (Complex::separator == comma)
			&& (Complex::rightBrace == rightBrace))
		{
			re = real;
			im = imaganary;
		}
		else {
			istrm.setstate(std::ios_base::failbit);
		}
	}
	return istrm;
}
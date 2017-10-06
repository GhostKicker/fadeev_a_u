#include "vec3d.h"
#include <iostream>
#include <sstream>

Vec3d operator+(const Vec3d& lhs, const Vec3d& rhs) {
	Vec3d l(lhs);
	l += rhs;
	return l;
}
Vec3d operator-(const Vec3d& lhs, const Vec3d& rhs) {
	Vec3d l(lhs);
	l -= rhs;
	return l;
}

Vec3d& Vec3d::operator+=(const Vec3d& rhs) {
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	return *this;
}

Vec3d& Vec3d::operator-=(const Vec3d& rhs) {
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	return *this;
}
Vec3d& Vec3d::operator*=(const double& rhs) {
	x *= rhs;
	y *= rhs;
	z *= rhs;
	return *this;
}
Vec3d& Vec3d::operator/=(const double& rhs) {
	x /= rhs;
	y /= rhs;
	z /= rhs;
	return *this;
}

Vec3d& Vec3d::operator=(const Vec3d& rhs) {
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
	return *this;
}



std::istream& Vec3d::readFrom(std::istream& istrm)
{
	char leftBrace(0);
	double xi(0.0);
	char dotcomma1(0);
	double yi(0.0);
	char dotcomma2(0);
	double zi(0.0);
	char rightBrace(0);
	istrm >> leftBrace >> xi >> dotcomma1 >> yi >> dotcomma2 >> zi >> rightBrace;
	if (istrm.good())
	{
		bool a = leftBrace == Vec3d::leftBrace;
		bool b = dotcomma1 == Vec3d::dotcomma;
		bool c = dotcomma2 == Vec3d::dotcomma;
		bool d = rightBrace == Vec3d::rightBrace;
		if (a && b && c && d) {
			x = xi;
			y = yi;
			z = zi;
		}
		else {
			istrm.setstate(std::ios_base::failbit);
		}
	}


	return istrm;
}

std::ostream& Vec3d::writeTo(std::ostream& ostrm) const 
{
	ostrm << leftBrace << x << dotcomma << y << dotcomma << z << rightBrace;
	return ostrm;
}

std::istream& operator>>(std::istream& istrm, Vec3d& rhs) {
	return rhs.readFrom(istrm);
}
std::ostream& operator<<(std::ostream& ostrm, const Vec3d& rhs) {
	return rhs.writeTo(ostrm);
}

double eps = 0.00001;
bool Vec3d::operator==(const Vec3d& rhs) {
	bool a = true;
	!(abs(x - rhs.x) < eps) ? a = false : a = a;
	!(abs(y - rhs.y) < eps) ? a = false : a = a;
	!(abs(z - rhs.z) < eps) ? a = false : a = a;
	return a;
}

bool  Vec3d::operator!=(const Vec3d& rhs) {
	return (operator==(rhs));
}

Vec3d operator-(const Vec3d& rhs) {
	double x = -rhs.x;
	double y = -rhs.y;
	double z = -rhs.z;
	return Vec3d(x, y, z);
}

Vec3d operator*(const Vec3d& lhs, const double& rhs) {
	Vec3d g = lhs;
	return g.operator*=(rhs);
}

Vec3d operator/(const Vec3d& lhs, const double& rhs) {
	Vec3d g = lhs;
	return g.operator/=(rhs);
}

Vec3d operator*(const double& lhs, const Vec3d& rhs) {
	double a = lhs;
	Vec3d b = rhs;
	return b.operator*=(a);
}
double Vec3d::length() const {
	double res(0);
	res += x * x;
	res += y * y;
	res += z * z;
	res = sqrt(res);
	return res;
}
double dotProduct(const Vec3d& lhs, const Vec3d& rhs) {
	double res = 0;
	res += lhs.x * rhs.x;
	res += lhs.y * rhs.y;
	res += lhs.z * rhs.z;
	return res;
}
Vec3d crossProduct(const Vec3d& lhs, const Vec3d& rhs) {
	double x = lhs.y * rhs.z - lhs.z * rhs.y;
	double y = lhs.z * rhs.x - lhs.x * rhs.z;
	double z = lhs.x * rhs.y - lhs.y * rhs.x;
	return Vec3d(x, y, z);
}
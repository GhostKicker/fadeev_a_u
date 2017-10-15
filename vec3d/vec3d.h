#ifndef VEC3D_H
#define VEC3D_H
#include <iosfwd>

struct Vec3d {

public:
    std::istream& Vec3d::readFrom(std::istream& istrm);
    std::ostream& Vec3d::writeTo(std::ostream& ostrm) const;

    Vec3d& operator+=(const Vec3d& rhs);
    Vec3d& operator-=(const Vec3d& rhs);

    Vec3d& operator*=(const double& rhs);
    Vec3d& operator/=(const double& rhs);

    bool operator==(const Vec3d& rhs);
    bool operator!=(const Vec3d& rhs);

    Vec3d& operator=(const Vec3d& rhs);


    double length() const;

    Vec3d(const double xin, const double yin, const double zin)
        : x(xin)
        , y(yin)
        , z(zin)
    {
    }

    Vec3d(const Vec3d& v) = default;
    Vec3d() = default;
    ~Vec3d() = default;

public:

    double x = 0.0;
    double y = 0.0;
    double z = 0.0;

    static const char leftBrace = '{';
    static const char rightBrace = '}';
    static const char dotcomma = ';';

};

Vec3d operator-(const Vec3d& rhs);

Vec3d operator+(const Vec3d& lhs, const Vec3d& rhs);
Vec3d operator-(const Vec3d& lhs, const Vec3d& rhs);

Vec3d operator*(const Vec3d& lhs, const double& rhs);
Vec3d operator/(const Vec3d& lhs, const double& rhs);
Vec3d operator*(const double& lhs, const Vec3d& rhs);

std::istream& operator>>(std::istream& istrm, Vec3d& rhs);
std::ostream& operator<<(std::ostream& ostrm, const Vec3d& rhs);

double dotProduct(const Vec3d& lhs, const Vec3d& rhs);
Vec3d crossProduct(const Vec3d& lhs, const Vec3d& rhs);

#endif // VEC3D_H
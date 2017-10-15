#ifndef  VEC3DT_H
#define VEC3DT_H

template<typename T>
struct Vec3dT
{
public:
    Vec3dT() = default;
    Vec3dT(const Vec3dT& v) = default;
    Vec3dT(const T& xi, const T& yi, const T& zi);
    ~Vec3dT() = default;


    Vec3dT& operator+=(const Vec3dT& rhs);
    Vec3dT& operator-=(const Vec3dT& rhs);

    bool operator==(const Vec3dT& rhs);
    bool operator!=(const Vec3dT& rhs);

    Vec3dT& operator=(const Vec3dT& rhs);

public:
	T x{ T() };
	T y{ T() };
	T z{ T() };

    static const char leftBrace = '{';
    static const char rightBrace = '}';
    static const char dotcomma = ';';


};

template <typename T>
bool Vec3dT<T>::operator==(const Vec3dT<T>& rhs) {
    if ((x == rhs.x) && (y == rhs.y) && (z == rhs.z)) {
        return true;
    }
    else {
        return false;
    }
}

template <typename T>
bool Vec3dT<T>::operator!=(const Vec3dT<T>& rhs) {
    return (!operator==(rhs));
}

template <typename T>
Vec3dT<T>& Vec3dT<T>::operator+=(const Vec3dT<T>& rhs) {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
}

template <typename T>
Vec3dT<T> operator+(const Vec3dT<T>& lhs, const Vec3dT<T>& rhs) {
    Vec3dT<T> l(lhs);
    l += rhs;
    return l;
}

template <typename T>
Vec3dT<T>& Vec3dT<T>::operator-=(const Vec3dT<T>& rhs) {
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return *this;
}

template <typename T>
Vec3dT<T> operator-(const Vec3dT<T>& lhs, const Vec3dT<T>& rhs) {
    Vec3dT<T> l(lhs);
    l -= rhs;
    return l;
}

template <typename T>
Vec3dT<T>::Vec3dT(const T& xi, const T& yi, const T& zi)
    : x{ xi }
    , y{ yi }
    , z{ zi }
{
};

template <typename T>
Vec3dT<T>& Vec3dT<T>::operator=(const Vec3dT<T>& rhs) {
    x = rhs.x;
    y = rhs.y;
    z = rhs.z;
    return *this;
}

double eps = 0.000001;
bool Vec3dT<double>::operator==(const Vec3dT<double>& rhs) {
    if (
        (abs(x - rhs.x) < eps) &&
        (abs(y - rhs.y) < eps) &&
        (abs(z - rhs.z) < eps)
        )
    {
        return true;
    }
    else
    {
        return false;
    }

}

#endif //  VEC3DT_H

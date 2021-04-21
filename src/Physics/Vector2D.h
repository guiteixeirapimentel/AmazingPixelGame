#ifndef VECTOR2D_H
#define VECTOR2D_H
#include <cmath>

template <class T>
class Vector2D
{
public:
    Vector2D(T x, T y) : cX(x), cY(y){};
    Vector2D(const Vector2D &v) : cX(v.cX), cY(v.cY){};
    Vector2D() : cX(0), cY(0){};
    ~Vector2D() {}

    T DotProduct(const Vector2D<T> &rhs) const
    {
        return (cX * rhs.cX) + (cY * rhs.cY);
    }

    T FakeVecProduct(const Vector2D<T> &rhs) const
    {
        return (cX * rhs.cY) - (cY * rhs.cX);
    }

    T GetMagnitudeSquared() const
    {
        return DotProduct(*this);
    }

    T GetMagnitude() const
    {
        return sqrt(GetMagnitudeSquared());
    }

    Vector2D<T> operator+(const Vector2D<T> rhs) const
    {
        return {cX + rhs.cX, cY + rhs.cY};
    }

    Vector2D<T> operator-(const Vector2D<T> rhs) const
    {
        return {cX - rhs.cX, cY - rhs.cY};
    }

    Vector2D<T> operator*(const T scalar) const
    {
        return {cX * scalar, cY * scalar};
    }

    Vector2D<T> operator/(const T scalar) const
    {
        return {cX / scalar, cY / scalar};
    }

    Vector2D<T> operator+=(const Vector2D<T> rhs)
    {
        cX += rhs.cX;
        cY += rhs.cY;
        return *this;
    }

    Vector2D<T> operator-=(const Vector2D<T> rhs)
    {
        cX -= rhs.cX;
        cY -= rhs.cY;
        return *this;
    }

    Vector2D<T> operator*=(const T scalar)
    {
        cX *= scalar;
        cY *= scalar;
        return *this;
    }

    Vector2D<T> operator/=(const T scalar)
    {
        cX /= scalar;
        cY /= scalar;
        return *this;
    }

    Vector2D<T> operator-() const{
        Vector2D<T> res;
        res.cX = -cX;
        res.cY = -cY;
        
        return res;
    }

public:
    T cX;
    T cY;
};

typedef Vector2D<float> Vector2DF;
typedef Vector2D<double> Vector2DD;
typedef Vector2D<int> Vector2DI;

#endif
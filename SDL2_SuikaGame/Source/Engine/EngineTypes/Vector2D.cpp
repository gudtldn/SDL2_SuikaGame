#include "Vector2D.h"
#include <compare>
#include <cmath>


Vector2D::Vector2D()
    : X(0.0)
    , Y(0.0)
{
}

Vector2D::Vector2D(double value)
    : X(value)
    , Y(value)
{
}

Vector2D::Vector2D(double x, double y)
    : X(x)
    , Y(y)
{
}

Vector2D Vector2D::Zero()
{
    return Vector2D(0.0, 0.0);
}

Vector2D Vector2D::One()
{
    return Vector2D(1.0, 1.0);
}

Vector2D Vector2D::CrossProduct(const Vector2D& lhs, const Vector2D& rhs)
{
    return Vector2D(lhs.X * rhs.Y, lhs.Y * rhs.X);
}

double Vector2D::DotProduct(const Vector2D& lhs, const Vector2D& rhs)
{
    return lhs.X * rhs.X + lhs.Y * rhs.Y;
}

double Vector2D::Length() const
{
    return sqrt(X * X + Y * Y);
}

double Vector2D::LengthSquared() const
{
    return X * X + Y * Y;
}

Vector2D Vector2D::Normalize() const
{
    double length = Length();
    return Vector2D(X / length, Y / length);
}

double Vector2D::Dot(const Vector2D& rhs) const
{
    return X * rhs.X + Y * rhs.Y;
}

double Vector2D::Cross(const Vector2D& rhs) const
{
    return X * rhs.Y - Y * rhs.X;
}

bool Vector2D::IsZero(double tolerance) const
{
    return std::abs(X) <= tolerance && std::abs(Y) <= tolerance;
}

bool Vector2D::Equals(const Vector2D& rhs, double tolerance) const
{
    return std::abs(X - rhs.X) <= tolerance && std::abs(Y - rhs.Y) <= tolerance;
}

Vector2D Vector2D::operator+(const Vector2D& rhs) const
{
    return Vector2D(X + rhs.X, Y + rhs.Y);
}

Vector2D Vector2D::operator+(double value) const
{
    return Vector2D(X + value, Y + value);
}

Vector2D& Vector2D::operator+=(const Vector2D& rhs)
{
    X += rhs.X;
    Y += rhs.Y;
    return *this;
}

Vector2D& Vector2D::operator+=(double value)
{
    X += value;
    Y += value;
    return *this;
}

Vector2D Vector2D::operator-(const Vector2D& rhs) const
{
    return Vector2D(X - rhs.X, Y - rhs.Y);
}

Vector2D Vector2D::operator-(double value) const
{
    return Vector2D(X - value, Y - value);
}

Vector2D& Vector2D::operator-=(const Vector2D& rhs)
{
    X -= rhs.X;
    Y -= rhs.Y;
    return *this;
}

Vector2D& Vector2D::operator-=(double value)
{
    X -= value;
    Y -= value;
    return *this;
}

Vector2D Vector2D::operator*(const Vector2D& rhs) const
{
    return Vector2D(X * rhs.X, Y * rhs.Y);
}

Vector2D Vector2D::operator*(double value) const
{
    return Vector2D(X * value, Y * value);
}

Vector2D& Vector2D::operator*=(const Vector2D& rhs)
{
    X *= rhs.X;
    Y *= rhs.Y;
    return *this;
}

Vector2D& Vector2D::operator*=(double value)
{
    X *= value;
    Y *= value;
    return *this;
}

bool Vector2D::operator==(const Vector2D& rhs) const
{
    return X == rhs.X && Y == rhs.Y;
}

bool Vector2D::operator!=(const Vector2D& rhs) const
{
    return !(*this == rhs);
}

std::partial_ordering Vector2D::operator<=>(const Vector2D& rhs) const
{
    double lhs_length = Length();
    double rhs_length = rhs.Length();

    if (lhs_length < rhs_length)
    {
        return std::partial_ordering::less;
    }

    if (lhs_length > rhs_length)
    {
        return std::partial_ordering::greater;
    }

    return (X == rhs.X && Y == rhs.Y) ? std::partial_ordering::equivalent : std::partial_ordering::unordered;
}

Vector2D Vector2D::operator-() const
{
    return Vector2D(-X, -Y);
}

double Vector2D::operator^(const Vector2D& rhs) const
{
    return Cross(rhs);
}

double Vector2D::operator|(const Vector2D& rhs) const
{
    return Dot(rhs);
}

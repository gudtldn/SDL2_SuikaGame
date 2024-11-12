#include "Vector2D.h"
#include <compare>


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

double Vector2D::DotProduct(const Vector2D& lhs, const Vector2D& rhs)
{
    return lhs | rhs;
}

double Vector2D::CrossProduct(const Vector2D& lhs, const Vector2D& rhs)
{
    return lhs ^ rhs;
}

double Vector2D::DistanceSquared(const Vector2D& lhs, const Vector2D& rhs)
{
    return Math::Square(rhs.X - lhs.X) + Math::Square(rhs.Y - lhs.Y);
}

double Vector2D::Distance(const Vector2D& lhs, const Vector2D& rhs)
{
    return Math::Sqrt(DistanceSquared(lhs, rhs));
}

Vector2D Vector2D::Clamp(const Vector2D& value, const Vector2D& min, const Vector2D& max)
{
    return Vector2D(
        Math::Clamp(value.X, min.X, max.X),
        Math::Clamp(value.Y, min.Y, max.Y)
    );
}

Vector2D Vector2D::Clamp(const Vector2D& value, double min, double max)
{
    return Vector2D(
        Math::Clamp(value.X, min, max),
        Math::Clamp(value.Y, min, max)
    );
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
    return *this | rhs;
}

double Vector2D::Cross(const Vector2D& rhs) const
{
    return *this ^ rhs;
}

bool Vector2D::IsNearlyZero(double tolerance) const
{
    return Math::Abs(X) <= tolerance && Math::Abs(Y) <= tolerance;
}

bool Vector2D::IsZero() const
{
    return X == 0.0 && Y == 0.0;
}

bool Vector2D::Equals(const Vector2D& rhs, double tolerance) const
{
    return Math::Abs(X - rhs.X) <= tolerance && Math::Abs(Y - rhs.Y) <= tolerance;
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

Vector2D Vector2D::operator/(const Vector2D& rhs) const
{
    return Vector2D(X / rhs.X, Y / rhs.Y);
}

Vector2D Vector2D::operator/(double value) const
{
    return Vector2D(X / value, Y / value);
}

Vector2D& Vector2D::operator/=(const Vector2D& rhs)
{
    X /= rhs.X;
    Y /= rhs.Y;
    return *this;
}

Vector2D& Vector2D::operator/=(double value)
{
    X /= value;
    Y /= value;
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

double Vector2D::operator|(const Vector2D& rhs) const
{
    return X * rhs.X + Y * rhs.Y;
}

double Vector2D::operator^(const Vector2D& rhs) const
{
    return X * rhs.Y - Y * rhs.X;
}

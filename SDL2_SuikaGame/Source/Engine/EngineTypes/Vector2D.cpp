#include "Vector2D.h"
#include <compare>


Vector2D Vector2D::Zero = Vector2D(0.0, 0.0);
Vector2D Vector2D::One = Vector2D(1.0, 1.0);

Vector2D::Vector2D()
    : X(0.0f)
    , Y(0.0f)
{
}

Vector2D::Vector2D(float value)
    : X(value)
    , Y(value)
{
}

Vector2D::Vector2D(float x, float y)
    : X(x)
    , Y(y)
{
}


float Vector2D::DotProduct(const Vector2D& lhs, const Vector2D& rhs)
{
    return lhs | rhs;
}

float Vector2D::CrossProduct(const Vector2D& lhs, const Vector2D& rhs)
{
    return lhs ^ rhs;
}

float Vector2D::DistanceSquared(const Vector2D& lhs, const Vector2D& rhs)
{
    return Math::Square(rhs.X - lhs.X) + Math::Square(rhs.Y - lhs.Y);
}

float Vector2D::Distance(const Vector2D& lhs, const Vector2D& rhs)
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

Vector2D Vector2D::Clamp(const Vector2D& value, float min, float max)
{
    return Vector2D(
        Math::Clamp(value.X, min, max),
        Math::Clamp(value.Y, min, max)
    );
}

float Vector2D::Length() const
{
    return sqrt(X * X + Y * Y);
}

float Vector2D::LengthSquared() const
{
    return X * X + Y * Y;
}

Vector2D Vector2D::Normalize() const
{
    float length = Length();
    return Vector2D(X / length, Y / length);
}

float Vector2D::DistanceTo(const Vector2D& rhs) const
{
    return Distance(*this, rhs);
}

float Vector2D::Dot(const Vector2D& rhs) const
{
    return *this | rhs;
}

float Vector2D::Cross(const Vector2D& rhs) const
{
    return *this ^ rhs;
}

bool Vector2D::IsNearlyZero(float tolerance) const
{
    return Math::Abs(X) <= tolerance && Math::Abs(Y) <= tolerance;
}

bool Vector2D::IsZero() const
{
    return X == 0.0 && Y == 0.0;
}

bool Vector2D::Equals(const Vector2D& rhs, float tolerance) const
{
    return Math::Abs(X - rhs.X) <= tolerance && Math::Abs(Y - rhs.Y) <= tolerance;
}

Vector2D Vector2D::operator+(const Vector2D& rhs) const
{
    return Vector2D(X + rhs.X, Y + rhs.Y);
}

Vector2D Vector2D::operator+(float value) const
{
    return Vector2D(X + value, Y + value);
}

Vector2D& Vector2D::operator+=(const Vector2D& rhs)
{
    X += rhs.X;
    Y += rhs.Y;
    return *this;
}

Vector2D& Vector2D::operator+=(float value)
{
    X += value;
    Y += value;
    return *this;
}

Vector2D Vector2D::operator-(const Vector2D& rhs) const
{
    return Vector2D(X - rhs.X, Y - rhs.Y);
}

Vector2D Vector2D::operator-(float value) const
{
    return Vector2D(X - value, Y - value);
}

Vector2D& Vector2D::operator-=(const Vector2D& rhs)
{
    X -= rhs.X;
    Y -= rhs.Y;
    return *this;
}

Vector2D& Vector2D::operator-=(float value)
{
    X -= value;
    Y -= value;
    return *this;
}

Vector2D Vector2D::operator*(const Vector2D& rhs) const
{
    return Vector2D(X * rhs.X, Y * rhs.Y);
}

Vector2D Vector2D::operator*(float value) const
{
    return Vector2D(X * value, Y * value);
}

Vector2D& Vector2D::operator*=(const Vector2D& rhs)
{
    X *= rhs.X;
    Y *= rhs.Y;
    return *this;
}

Vector2D& Vector2D::operator*=(float value)
{
    X *= value;
    Y *= value;
    return *this;
}

Vector2D Vector2D::operator/(const Vector2D& rhs) const
{
    return Vector2D(X / rhs.X, Y / rhs.Y);
}

Vector2D Vector2D::operator/(float value) const
{
    return Vector2D(X / value, Y / value);
}

Vector2D& Vector2D::operator/=(const Vector2D& rhs)
{
    X /= rhs.X;
    Y /= rhs.Y;
    return *this;
}

Vector2D& Vector2D::operator/=(float value)
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
    float lhs_length = Length();
    float rhs_length = rhs.Length();

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

float Vector2D::operator|(const Vector2D& rhs) const
{
    return X * rhs.X + Y * rhs.Y;
}

float Vector2D::operator^(const Vector2D& rhs) const
{
    return X * rhs.Y - Y * rhs.X;
}

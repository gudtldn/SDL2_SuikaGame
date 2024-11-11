#pragma once

// forward declaration
namespace std
{
    struct partial_ordering;
}


/// @brief 2차원 벡터 클래스
class Vector2D
{
public:
    double X;
    double Y;

public:
    Vector2D();
    Vector2D(double value);
    Vector2D(double x, double y);

    /****** Static Methods ******/

    /// @brief (0, 0) 벡터를 반환합니다.
    static Vector2D Zero();

    /// @brief (1, 1) 벡터를 반환합니다.
    static Vector2D One();

    /// @brief 두 벡터의 내적을 반환합니다.
    static Vector2D CrossProduct(const Vector2D& lhs, const Vector2D& rhs);

    /// @brief 두 벡터의 외적을 반환합니다.
    static double DotProduct(const Vector2D& lhs, const Vector2D& rhs);

    /****** Methods ******/

    /// @brief 벡터의 길이를 반환합니다.
    /// @return 벡터의 길이
    double Length() const;

    /// @brief 벡터의 길이의 제곱을 반환합니다.
    /// @return 벡터의 길이의 제곱
    double LengthSquared() const;

    /// @brief 벡터를 정규화합니다.
    /// @return 정규화된 벡터
    Vector2D Normalize() const;

    /// @brief 벡터의 내적을 반환합니다.
    /// @param rhs 내적을 계산할 벡터
    /// @return 내적
    double Dot(const Vector2D& rhs) const;

    /// @brief 벡터의 외적을 반환합니다.
    /// @param rhs 외적을 계산할 벡터
    /// @return 외적
    double Cross(const Vector2D& rhs) const;

    /// @brief 벡터가 거의 0 벡터인지 확인합니다.
    /// @param tolerance 허용 오차 default: 1.e-6
    /// @return 거의 0 벡터이면 true, 아니면 false
    bool IsZero(double tolerance = 1.e-6) const;

    /// @brief 벡터가 거의 같은지 확인합니다.
    /// @param rhs 비교할 벡터
    /// @param tolerance 허용 오차 default: 1.e-6
    /// @return 거의 같으면 true, 아니면 false
    bool Equals(const Vector2D& rhs, double tolerance = 1.e-6) const;


    /****** Operator Overloading ******/

    // 사칙연산
    Vector2D operator+(const Vector2D& rhs) const;
    Vector2D operator+(double value) const;
    Vector2D& operator+=(const Vector2D& rhs);
    Vector2D& operator+=(double value);

    Vector2D operator-(const Vector2D& rhs) const;
    Vector2D operator-(double value) const;
    Vector2D& operator-=(const Vector2D& rhs);
    Vector2D& operator-=(double value);

    Vector2D operator*(const Vector2D& rhs) const;
    Vector2D operator*(double value) const;
    Vector2D& operator*=(const Vector2D& rhs);
    Vector2D& operator*=(double value);

    // 비교 연산
    bool operator==(const Vector2D& rhs) const;
    bool operator!=(const Vector2D& rhs) const;
    std::partial_ordering operator<=>(const Vector2D& rhs) const;

    // 단항 연산
    Vector2D operator-() const;

    // Cross Product
    double operator^(const Vector2D& rhs) const;

    // Dot Product
    double operator|(const Vector2D& rhs) const;
};

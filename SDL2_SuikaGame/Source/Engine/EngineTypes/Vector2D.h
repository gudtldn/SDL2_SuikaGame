#pragma once
#include"Engine/Utils/Math.h"

// forward declaration
namespace std
{
    struct partial_ordering;
}


/// @brief 2차원 벡터 클래스
class Vector2D
{
public:
    float X;
    float Y;

public:
    Vector2D();
    Vector2D(float value);
    Vector2D(float x, float y);

    /****** Static Methods ******/

    /// @brief (0, 0) 벡터를 반환합니다.
    static Vector2D Zero;

    /// @brief (1, 1) 벡터를 반환합니다.
    static Vector2D One;

    /// @brief 두 벡터의 외적을 반환합니다.
    static float DotProduct(const Vector2D& lhs, const Vector2D& rhs);

    /// @brief 두 벡터의 내적을 반환합니다.
    static float CrossProduct(const Vector2D& lhs, const Vector2D& rhs);

    /// @brief 두 벡터의 거리의 제곱을 반환합니다.
    static float DistanceSquared(const Vector2D& lhs, const Vector2D& rhs);

    /// @brief 두 벡터의 거리를 반환합니다.
    static float Distance(const Vector2D& lhs, const Vector2D& rhs);

    /// @brief 벡터를 최솟값과 최댓값 사이로 Clamp합니다.
    static Vector2D Clamp(const Vector2D& value, const Vector2D& min, const Vector2D& max);
    static Vector2D Clamp(const Vector2D& value, float min, float max);


    /****** Methods ******/

    /// @brief 벡터의 길이를 반환합니다.
    /// @return 벡터의 길이
    float Length() const;

    /// @brief 벡터의 길이의 제곱을 반환합니다.
    /// @return 벡터의 길이의 제곱
    float LengthSquared() const;

    /// @brief 벡터를 정규화합니다.
    /// @return 정규화된 벡터
    Vector2D Normalize() const;

    /// @brief 벡터의 내적을 반환합니다.
    /// @param rhs 내적을 계산할 벡터
    /// @return 내적
    float Dot(const Vector2D& rhs) const;

    /// @brief 벡터의 외적을 반환합니다.
    /// @param rhs 외적을 계산할 벡터
    /// @return 외적
    float Cross(const Vector2D& rhs) const;

    /// @brief 벡터가 거의 0 벡터인지 확인합니다.
    /// @param tolerance 허용 오차 default: 1.e-4
    /// @return 거의 0 벡터이면 true, 아니면 false
    bool IsNearlyZero(float tolerance = KINDA_SMALL_NUMBER) const;

    /// @brief 벡터가 0 벡터인지 확인합니다.
    /// @return 0 벡터이면 true, 아니면 false
    bool IsZero() const;

    /// @brief 벡터가 거의 같은지 확인합니다.
    /// @param rhs 비교할 벡터
    /// @param tolerance 허용 오차 default: 1.e-4
    /// @return 거의 같으면 true, 아니면 false
    bool Equals(const Vector2D& rhs, float tolerance = KINDA_SMALL_NUMBER) const;


    /****** Operator Overloading ******/

    // 사칙연산
    Vector2D operator+(const Vector2D& rhs) const;
    Vector2D operator+(float value) const;
    Vector2D& operator+=(const Vector2D& rhs);
    Vector2D& operator+=(float value);

    Vector2D operator-(const Vector2D& rhs) const;
    Vector2D operator-(float value) const;
    Vector2D& operator-=(const Vector2D& rhs);
    Vector2D& operator-=(float value);

    Vector2D operator*(const Vector2D& rhs) const;
    Vector2D operator*(float value) const;
    Vector2D& operator*=(const Vector2D& rhs);
    Vector2D& operator*=(float value);

    Vector2D operator/(const Vector2D& rhs) const;
    Vector2D operator/(float value) const;
    Vector2D& operator/=(const Vector2D& rhs);
    Vector2D& operator/=(float value);

    // 비교 연산
    bool operator==(const Vector2D& rhs) const;
    bool operator!=(const Vector2D& rhs) const;
    std::partial_ordering operator<=>(const Vector2D& rhs) const;

    // 단항 연산
    Vector2D operator-() const;

    // Dot Product
    float operator|(const Vector2D& rhs) const;

    // Cross Product
    float operator^(const Vector2D& rhs) const;
};

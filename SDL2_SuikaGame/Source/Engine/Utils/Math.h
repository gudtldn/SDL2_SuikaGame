#pragma once
#include <type_traits>

/// @brief 수학 관련 유틸리티 함수들을 포함하는 네임스페이스
namespace Math
{

/// @brief PI 값
static constexpr double PI = 3.14159265358979323846;

/// @brief 두 값 중에서 최솟값을 반환합니다.
/// @tparam T 임의의 숫자 타입
/// @param a 비교할 값
/// @param b 비교할 값
/// @return 최솟값
template <typename T> requires std::is_arithmetic_v<T>
inline T Min(T a, T b)
{
    return a < b ? a : b;
}

/// @brief 두 값 중에서 최댓값을 반환합니다.
/// @tparam T 임의의 숫자 타입
/// @param a 비교할 값
/// @param b 비교할 값
/// @return 최댓값
template <typename T> requires std::is_arithmetic_v<T>
inline T Max(T a, T b)
{
    return a > b ? a : b;
}

/// @brief 두 값 중에서 최솟값과 최댓값을 반환합니다.
/// @tparam T 임의의 숫자 타입
/// @param a 비교할 값
/// @param b 비교할 값
/// @param min 최솟값
/// @param max 최댓값
/// @return 최솟값과 최댓값 사이의 값
template <typename T> requires std::is_arithmetic_v<T>
inline T Clamp(T value, T min, T max)
{
    return Min(Max(value, min), max);
}

} // namespace Math
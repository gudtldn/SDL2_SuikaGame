#pragma once
#include <cmath>
#include <cstdlib>
#include <type_traits>


#define PI                 (3.1415926535897932f)
#define SMALL_NUMBER       (1.e-8f)
#define KINDA_SMALL_NUMBER (1.e-4f)

#define PI_DOUBLE          (3.141592653589793238462643383279502884197169399)
#define SMALL_NUMBER_DOUBLE (1.e-8)
#define KINDA_SMALL_NUMBER_DOUBLE (1.e-4)


/// @brief 수학 관련 유틸리티 함수들을 포함하는 구조체
struct Math
{
    /// @brief 절대값을 반환합니다.
    /// @tparam T 임의의 숫자 타입
    /// @param value 값
    /// @return 절대값
    template <typename T> requires std::is_arithmetic_v<T>
    [[nodiscard]] static constexpr T Abs(T value)
    {
        return value >= 0 ? value : -value;
    }

    /// @brief 두 값 중에서 최솟값을 반환합니다.
    /// @tparam T 임의의 숫자 타입
    /// @param a 비교할 값
    /// @param b 비교할 값
    /// @return 최솟값
    template <typename T> requires std::is_arithmetic_v<T>
    [[nodiscard]] static constexpr T Min(T a, T b)
    {
        return a < b ? a : b;
    }

    /// @brief 두 값 중에서 최댓값을 반환합니다.
    /// @tparam T 임의의 숫자 타입
    /// @param a 비교할 값
    /// @param b 비교할 값
    /// @return 최댓값
    template <typename T> requires std::is_arithmetic_v<T>
    [[nodiscard]] static constexpr T Max(T a, T b)
    {
        return a > b ? a : b;
    }

    /// @brief 두 값 중에서 최솟값과 최댓값을 반환합니다.
    /// @tparam T 임의의 숫자 타입
    /// @param value 비교할 값
    /// @param min 최솟값
    /// @param max 최댓값
    /// @return 최솟값과 최댓값 사이의 값
    template <typename T> requires std::is_arithmetic_v<T>
    [[nodiscard]] static constexpr T Clamp(T value, T min, T max)
    {
        return Min(Max(value, min), max);
    }

    /// @brief 두 값이 거의 같은지 비교합니다.
    /// @tparam T 임의의 숫자 타입
    /// @param a 첫 번째 값
    /// @param b 두 번째 값
    /// @param tolerance 허용 오차
    /// @return 두 값이 거의 같은지 여부
    template <typename T> requires std::is_floating_point_v<T>
    [[nodiscard]] static constexpr bool IsNearlyEqual(T a, T b, T tolerance = SMALL_NUMBER)
    {
        return Abs(a - b) <= tolerance;
    }

    /// @brief 값이 거의 0인지 비교합니다.
    /// @tparam T 임의의 숫자 타입
    /// @param value 값
    /// @param tolerance 허용 오차
    /// @return 값이 거의 0인지 여부
    template <typename T> requires std::is_floating_point_v<T>
    [[nodiscard]] static constexpr bool IsNearlyZero(T value, T tolerance = SMALL_NUMBER)
    {
        return Abs(value) <= tolerance;
    }

    /// @brief 값이 NaN인지 비교합니다.
    /// @tparam T 임의의 숫자 타입
    /// @param value 값
    /// @return 값이 NaN인지 여부
    template <typename T> requires std::is_floating_point_v<T>
    [[nodiscard]] static bool IsNaN(T value)
    {
        return isnan(value) != 0;
    }

    /// @brief 값이 무한대인지 비교합니다.
    /// @tparam T 임의의 숫자 타입
    /// @param value 값
    /// @return 값이 무한대인지 여부
    template <typename T> requires std::is_floating_point_v<T>
    [[nodiscard]] static bool IsInfinite(T value)
    {
        return isinf(value) != 0;
    }

    /// @brief Radian 값을 Degree로 변환합니다.
    /// @param radian 라디안 값
    /// @return degree 값
    [[nodiscard]] static float RadianToDegree(float radian)
    {
        return radian * 180.0f / PI;
    }

    /// @brief Degree 값을 Radian으로 변환합니다.
    /// @param degree degree 값
    /// @return 라디안 값
    [[nodiscard]] static float DegreeToRadian(float degree)
    {
        return degree * PI / 180.0f;
    }

    /// @brief Sin 함수를 계산합니다.
    /// @param value 각도
    /// @return Sin 함수 값
    [[nodiscard]] static double Sin(double value)
    {
        return sin(value);
    }

    [[nodiscard]] static float Sin(float value)
    {
        return sinf(value);
    }

    /// @brief Cos 함수를 계산합니다.
    /// @param value 각도
    /// @return Cos 함수 값
    [[nodiscard]] static double Cos(double value)
    {
        return cos(value);
    }

    [[nodiscard]] static float Cos(float value)
    {
        return cosf(value);
    }

    /// @brief Tan 함수를 계산합니다.
    /// @param value 각도
    /// @return Tan 함수 값
    [[nodiscard]] static double Tan(double value)
    {
        return tan(value);
    }

    [[nodiscard]] static float Tan(float value)
    {
        return tanf(value);
    }

    /// @brief ArcSin 함수를 계산합니다.
    /// @param value 값
    /// @return ArcSin 함수 값
    [[nodiscard]] static double Asin(double value)
    {
        return asin(value < -1.0 ? -1.0 : (value < 1.0 ? value : 1.0));
    }

    [[nodiscard]] static float Asin(float value)
    {
        return asinf(value < -1.0f ? -1.0f : (value < 1.0f ? value : 1.0f));
    }

    /// @brief ArcCos 함수를 계산합니다.
    /// @param value 값
    /// @return ArcCos 함수 값
    [[nodiscard]] static double Acos(double value)
    {
        // value가 -1.0보다 작으면 -1.0으로, 1.0보다 크면 1.0으로 설정합니다.
        return acos(value < -1.0 ? -1.0 : (value < 1.0 ? value : 1.0));
    }

    [[nodiscard]] static float Acos(float value)
    {
        return acosf(value < -1.0f ? -1.0f : (value < 1.0f ? value : 1.0f));
    }

    /// @brief ArcTan 함수를 계산합니다.
    /// @param value 값
    /// @return ArcTan 함수 값
    [[nodiscard]] static double Atan(double value)
    {
        return atan(value);
    }

    [[nodiscard]] static float Atan(float value)
    {
        return atanf(value);
    }

    /// @brief ArcTan2 함수를 계산합니다.
    /// @param y y 값
    /// @param x x 값
    [[nodiscard]] static double Atan2(double y, double x)
    {
        return atan2(y, x);
    }

    [[nodiscard]] static float Atan2(float y, float x)
    {
        return atan2f(y, x);
    }

    /// @brief 제곱근을 계산합니다.
    /// @param value 값
    /// @return 제곱근
    [[nodiscard]] static double Sqrt(double value)
    {
        return sqrt(value);
    }

    [[nodiscard]] static float Sqrt(float value)
    {
        return sqrtf(value);
    }

    /// @brief 제곱을 계산합니다.
    /// @param value 값
    /// @return 제곱
    template <typename T> requires std::is_arithmetic_v<T>
    [[nodiscard]] static constexpr T Square(T value)
    {
        return value * value;
    }

    /// @brief 선형 보간을 수행합니다.
    /// @tparam T 임의의 숫자 타입
    /// @param a 시작 값
    /// @param b 끝 값
    /// @param alpha 보간 계수
    /// @return 보간된 값
    template <typename T> requires std::is_arithmetic_v<T>
    [[nodiscard]] static constexpr T Lerp(T a, T b, float alpha)
    {
        return a + (b - a) * alpha;
    }


    /// @brief 랜덤 함수를 초기화합니다.
    static void RandInit(int seed)
    {
        srand(seed);
    }

    /// @brief min ~ max 사이의 랜덤 정수를 생성합니다.
    [[nodiscard]] static int RandRange(int min, int max)
    {
        const int range = (max - min) + 1;
		return min + RandHelper(range);
    }

    /// @brief min ~ max 사이의 랜덤 실수를 생성합니다.
    [[nodiscard]] static float RandRange(float min, float max)
    {
        return min + (max - min) * FRand();
    }

private:
    /// @brief 0 ~ RAND_MAX 사이의 랜덤 정수를 생성합니다.
    /// @return 랜덤 정수
    [[nodiscard]] static int Rand()
    {
        return rand();  // NOLINT(concurrency-mt-unsafe)
    }

    /// @brief 0 ~ 1 사이의 랜덤 실수를 생성합니다.
    /// @return 랜덤 실수
    [[nodiscard]] static float FRand()
    {
        // FP32 mantissa can only represent 24 bits before losing precision
        constexpr int RandMax = 0x00ffffff < RAND_MAX ? 0x00ffffff : RAND_MAX;
        return static_cast<float>(rand() & RandMax) / static_cast<float>(RandMax);  // NOLINT(concurrency-mt-unsafe)
    }

    /// @brief Helper function for rand implementations. Returns a random number in [0..A)
	[[nodiscard]] static int RandHelper(int A)
	{
		// Note that on some platforms RAND_MAX is a large number so we cannot do ((rand()/(RAND_MAX+1)) * A)
		// or else we may include the upper bound results, which should be excluded.
		return A > 0 ? Min(static_cast<int>(FRand() * static_cast<float>(A)), A - 1) : 0;
	}
}; // struct Math

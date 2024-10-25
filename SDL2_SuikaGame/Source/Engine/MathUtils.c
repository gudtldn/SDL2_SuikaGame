#include "MathUtils.h"
#include <math.h>


double Clamp(double value, double min, double max)
{
    if (value < min)
    {
        return min;
    }
    else if (value > max)
    {
        return max;
    }
    return value;
}

double Lerp(double a, double b, double alpha)
{
    // 선형 보간법
    // https://en.wikipedia.org/wiki/Linear_interpolation
    return a + (b - a) * alpha;
}

double InterpTo(double current, double target, double delta_time, double interp_speed)
{
    // 만약 보간 속도가 0 이하이면 목표값을 반환
    if (interp_speed <= 0.0)
    {
        return target;
    }

    // 도달할 거리
    double delta = target - current;

    // 거리가 너무 작으면 목표 위치로 설정
    if (delta * delta < 1e-8)
    {
        return target;
    }

    // 이동 거리, 너무 많이 이동하지 않도록 클램프
    double delta_move = delta * Clamp(delta_time * interp_speed, 0.0, 1.0);
    return current + delta_move;
}

bool IsNearlyZero(double value)
{
    return fabs(value) < 1e-4;
}

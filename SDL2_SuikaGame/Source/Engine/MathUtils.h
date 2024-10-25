#pragma once
#include <SDL.h>
#include <stdbool.h>


/// @brief 최솟값과 최댓값 사이의 값을 반환하는 함수
/// @param value 값
/// @param min 최솟값
/// @param max 최댓값
/// @return 최솟값과 최댓값 사이의 값
double Clamp(double value, double min, double max);

/// @brief 선형 보간 함수
/// @param a 보간 시작 값
/// @param b 보간 끝 값
/// @param alpha 보간 가중치 (0.0 ~ 1.0)
/// @return 보간 결과 값 
double Lerp(double a, double b, double alpha);

/// @brief 보간 함수
/// @param current 현재 값
/// @param target 목표 값
/// @param delta_time 경과 시간
/// @param interp_speed 보간 속도
/// @return 보간 결과 값
double InterpTo(double current, double target, double delta_time, double interp_speed);

/// @brief 두 값이 거의 같은지 비교하는 함수 (오차 범위: 0.0001)
/// @param value 비교할 값
bool IsNearlyZero(double value);

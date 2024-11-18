#pragma once
#include <cstdint>


/// @brief 렌더링 앵커
enum class RenderAnchor : uint8_t
{
    // TODO: 나중에 비트 플래그로 수정
    // (비트 플래그 ex: Top | Left)

    TopLeft,      // 왼쪽 상단
    TopCenter,    // 중앙 상단
    TopRight,     // 오른쪽 상단

    CenterLeft,   // 왼쪽 중앙
    Center,       // 중앙
    CenterRight,  // 오른쪽 중앙

    BottomLeft,   // 왼쪽 하단
    BottomCenter, // 중앙 하단
    BottomRight,  // 오른쪽 하단
};

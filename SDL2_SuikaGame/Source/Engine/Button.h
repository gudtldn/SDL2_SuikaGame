#pragma once
#include <SDL.h>
#include <stdbool.h>

// forward declaration
typedef struct View View;


/// @brief 버튼 구조체
typedef struct Button
{
    SDL_Rect rect;
    SDL_Texture* texture;
    bool is_hovered;
    bool is_clicked;
} Button;

/// @brief 버튼 생성
/// @param rect 버튼 위치 및 크기
/// @param texture 버튼 텍스처
Button CreateButton(SDL_Rect rect, SDL_Texture* texture);

/// @brief 버튼 업데이트
/// @param button 버튼 구조체
/// @param callback 버튼 클릭 시 호출할 콜백 함수
void UpdateHandleButton(View* view, Button* button, void (*callback)(View*));

/// @brief 버튼 렌더링
/// @param renderer SDL 렌더러
/// @param button 버튼 구조체
void RenderButton(SDL_Renderer* renderer, Button* button);

/// @brief 버튼 해제
/// @param button 버튼 구조체
void DestroyButton(Button* button);

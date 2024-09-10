#include "Key.h"

/// @brief 입력된 이벤트로부터 눌린 키를 반환
/// @param event SDL 이벤트
/// @return EBindingKey (게임에 사용되는 키)
EBindingKey GetPressedKey(SDL_Event* event)
{
    switch (event->key.keysym.sym)
    {
    case SDLK_ESCAPE:
        return KEY_ESCAPSE;
    case SDLK_w:
    case SDLK_UP:
        return KEY_UP;
    case SDLK_s:
    case SDLK_DOWN:
        return KEY_DOWN;
    case SDLK_a:
    case SDLK_LEFT:
        return KEY_LEFT;
    case SDLK_d:
    case SDLK_RIGHT:
        return KEY_RIGHT;
    default:
        return KEY_DEFAULT;
    }
}

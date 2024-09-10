#pragma once
#include <SDL.h>
#include <stdbool.h>

typedef enum EBindingKey
{
    KEY_DEFAULT,
    KEY_ESCAPSE,
    KEY_UP,
    KEY_DOWN,
    KEY_LEFT,
    KEY_RIGHT,
} EBindingKey;

EBindingKey GetPressedKey(SDL_Event* event);

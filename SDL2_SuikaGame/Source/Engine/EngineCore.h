#pragma once

// SDL
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <box2d/box2d.h>

// C++ Standard Library
#include <memory>
#include <cstdint>
#include <optional>
#include <expected>
#include <stdexcept>
#include <type_traits>

// Engine Headers
#include "GameEngine.h"
#include "GlobalMacro.h"
#include "LogMacros.h"

#include "Manager/SDLManager.h"
#include "Manager/ObjectManager.h"

#include "Components/Stage.h"
#include "Components/GameObject.h"

#include "Interfaces/IEventObserver.h"

#include "EngineTypes/Texture.h"
#include "EngineTypes/Vector2D.h"


// expr이 실패하면 throw std::runtime_error를 던집니다.
#define THROW_IF_FAILED(expr, fmt, ...)                          \
    if (!(expr))                                                 \
    {                                                            \
        LOG_ERROR(fmt, __VA_ARGS__);                             \
        throw std::runtime_error("Failed to expr: '" #expr "'"); \
    }

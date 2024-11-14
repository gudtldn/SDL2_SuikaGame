#pragma once

// SDL2 Library
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

// Box2D Library
#include <box2d/box2d.h>

// C++ Standard Library
#include <memory>

#include <optional>
#include <expected>
#include <stdexcept>
#include <type_traits>

// Engine Headers
#include "Engine/GameEngine.h"
#include "Engine/GlobalMacro.h"
#include "Engine/LogMacros.h"

#include "Engine/Manager/SDLManager.h"
#include "Engine/Manager/Box2DManager.h"
#include "Engine/Manager/ObjectManager.h"

#include "Engine/Components/Stage.h"
#include "Engine/Components/GameObject.h"

#include "Engine/EngineTypes/Texture2D.h"
#include "Engine/EngineTypes/FTexture2D.h"
#include "Engine/EngineTypes/Rectangle.h"
#include "Engine/EngineTypes/Vector2D.h"

#include "Engine/Utils/Math.h"


// expr이 실패하면 throw std::runtime_error를 던집니다.
#define THROW_IF_FAILED(expr, fmt, ...)                          \
    if (!(expr))                                                 \
    {                                                            \
        LOG_ERROR(fmt, __VA_ARGS__);                             \
        throw std::runtime_error("Failed to expr: '" #expr "'"); \
    }

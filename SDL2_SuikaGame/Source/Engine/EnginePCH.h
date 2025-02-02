#pragma once

// SDL2 Library
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

// Box2D Library
#include <box2d/box2d.h>

// C++ Standard Library
#include <array>
#include <vector>
#include <string>
#include <format>
#include <memory>
#include <optional>
#include <expected>
#include <stdexcept>
#include <type_traits>

// Engine Headers
#include "Engine/GameEngine.h"
#include "Engine/GlobalMacro.h"

#include "Engine/AbstractClasses/Stage.h"
#include "Engine/AbstractClasses/GameObject.h"
#include "Engine/AbstractClasses/GameResource.h"

#include "Engine/Manager/SDLManager.h"
#include "Engine/Manager/Box2DManager.h"
#include "Engine/Manager/ObjectManager.h"

#include "Engine/Components/TextRender.h"
#include "Engine/Components/Rectangle.h"
#include "Engine/Components/FTexture2D.h"
#include "Engine/Components/Texture2D.h"
#include "Engine/Components/TextureButtonComponent.h"

#include "Engine/EngineTypes/Vector2D.h"
#include "Engine/EngineTypes/RenderAnchor.h"

#include "Engine/Utils/Math.h"
#include "Engine/Utils/LogMacros.h"
#include "Engine/Utils/DelegateCombination.h"


// expr이 실패하면 throw std::runtime_error를 던집니다.
#define THROW_IF_FAILED(expr, fmt, ...)                                   \
    if (!(expr))                                                          \
    {                                                                     \
        LOG_ERROR(fmt, __VA_ARGS__);                                      \
        throw std::runtime_error(                                         \
            std::format("Failed to expr: '" #expr "'\n" fmt, __VA_ARGS__) \
        );                                                                \
    }

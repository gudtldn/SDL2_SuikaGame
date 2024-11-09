#pragma once

// SDL
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <box2d/box2d.h>


// C++ Standard Library
#include <memory>
#include <type_traits>
#include <optional>
#include <expected>
#include <stdexcept>


// Engine Headers
#include "App.h"
#include "GlobalMacro.h"

#include "Manager/SDLManager.h"
#include "Manager/ObjectManager.h"

#include "Components/Stage.h"
#include "Components/GameObject.h"

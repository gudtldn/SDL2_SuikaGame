#include "SDLManager.h"
#include "Engine/Utils/LogMacros.h"
#include "Engine/Components/Texture2D.h"

#include <stdexcept>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>


// 오류 핸들러
#define CHECK_AND_LOG_ERROR(condition, message, ...) \
    if (condition)                                   \
    {                                                \
        LOG_ERROR(message, ##__VA_ARGS__);           \
        throw std::runtime_error(SDL_GetError());    \
    }


SDLManager::SDLManager()
{
    // SDL 초기화
    CHECK_AND_LOG_ERROR(
        SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) < 0,
        "SDL could not initialize! SDL_Error: {}", SDL_GetError()
    )

    // SDL_Image 초기화
    CHECK_AND_LOG_ERROR(
        (IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) == 0,
        "SDL_image could not initialize! SDL_image Error: {}", IMG_GetError()
    )

    // SDL_TTF 초기화
    CHECK_AND_LOG_ERROR(
        TTF_Init() == -1,
        "SDL_ttf could not initialize! SDL_ttf Error: {}", TTF_GetError()
    )

    // SDL_Mixer 초기화
    CHECK_AND_LOG_ERROR(
        Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0,
        "SDL_mixer could not initialize! SDL_mixer Error: {}", Mix_GetError()
    )
}

SDLManager::~SDLManager()
{
    // SDL_Mixer 종료
    Mix_Quit();

    // SDL_TTF 종료
    TTF_Quit();

    // SDL_Image 종료
    IMG_Quit();

    // SDL 종료
    SDL_Quit();
}

std::unique_ptr<Texture2D> SDLManager::CaptureScreen(SDL_Renderer* renderer)
{
    int width, height;
    SDL_GetRendererOutputSize(renderer, &width, &height);

    SDL_Surface* surface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);  
    CHECK_AND_LOG_ERROR(
        surface == nullptr,
        "Failed to create surface for screen capture! SDL_Error: {}", SDL_GetError()
    )

    // 렌더러의 내용을 캡쳐
    if (
        SDL_RenderReadPixels(
            renderer,
            nullptr,
            SDL_PIXELFORMAT_ARGB8888,
            surface->pixels,
            surface->pitch
        ) != 0
    ) {
        LOG_ERROR("Failed to read pixels: {}", SDL_GetError());
        SDL_FreeSurface(surface);
        throw std::runtime_error(SDL_GetError());
    }

    std::unique_ptr<Texture2D> result = std::make_unique<Texture2D>(
        SDL_CreateTextureFromSurface(renderer, surface)
    );
    CHECK_AND_LOG_ERROR(
        result == nullptr,
        "Failed to create texture for screen capture! SDL_Error: {}", SDL_GetError()
    )

    SDL_FreeSurface(surface);
    return result;
}

#undef CHECK_AND_LOG_ERROR

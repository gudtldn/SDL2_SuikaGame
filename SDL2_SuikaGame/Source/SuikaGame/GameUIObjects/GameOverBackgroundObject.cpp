﻿#include "GameOverBackgroundObject.h"

GameOverBackgroundObject::GameOverBackgroundObject(GameEngine* engine)
    : GameObject(engine)
{
    z_order = -1;

    // 배경 이미지 로드
    SDL_Texture* raw_background_texture = IMG_LoadTexture(
        engine->GetRenderer(),
        "Contents/Textures/result_screen.png"
    );
    THROW_IF_FAILED(
        raw_background_texture,
        "Failed to load background texture! SDL Error: {}", SDL_GetError()
    )

    background_texture = std::make_unique<Texture2D>(
        raw_background_texture,
        Vector2D(
            SCREEN_WIDTH,
            SCREEN_HEIGHT
        )
    );

    // 검은색 반투명 배경
    background_rect = Rectangle({
        SCREEN_WIDTH,
        SCREEN_HEIGHT
    });
    background_rect.SetColor(0, 0, 0, 128);
    background_rect.SetBlendMode(SDL_BLENDMODE_BLEND);
}

void GameOverBackgroundObject::Render(SDL_Renderer* renderer) const
{
    background_rect.Render(renderer, {
        SCREEN_WIDTH / 2.0f,
        SCREEN_HEIGHT / 2.0f
    });
    background_texture->Render(renderer, {
        SCREEN_WIDTH / 2.0f,
        SCREEN_HEIGHT / 2.0f
    });
}

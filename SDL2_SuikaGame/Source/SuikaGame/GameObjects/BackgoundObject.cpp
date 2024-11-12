#include "BackgoundObject.h"


BackgoundObject::BackgoundObject(GameEngine* engine)
    : GameObject(engine)
    , background_color({ 0xDD, 0x8E, 0x40, 0xFF })
    , second_background_color({ 0xFF, 0xFE, 0xAA, 0xFF })
    , second_background_rect({
        .x = 0,
        .y = SCREEN_HEIGHT / 2 + (int)(SCREEN_HEIGHT * 0.1),
        .w = SCREEN_WIDTH,
        .h = SCREEN_HEIGHT / 2,
    })
{
    // 렌더링 순서 (배경은 가장 뒤에 렌더링)
    z_order = -2;
}

void BackgoundObject::Render(SDL_Renderer* renderer) const
{
    // 배경 색상 설정
    SDL_SetRenderDrawColor(renderer, 0xDD, 0x8E, 0x40, 0xFF);
    SDL_RenderClear(renderer);

    // 하이라이트 배경 색상 설정
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFE, 0xAA, 0xFF);
    SDL_RenderFillRect(renderer, &second_background_rect);
}

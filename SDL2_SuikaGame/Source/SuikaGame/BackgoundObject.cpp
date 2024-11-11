#include "BackgoundObject.h"


BackgoundObject::BackgoundObject(GameEngine* engine)
    : GameObject(engine)
{
    // 렌더링 순서 (배경은 가장 뒤에 렌더링)
    z_order = -1;
}

void BackgoundObject::Render(SDL_Renderer* renderer)
{
    // 배경 색상 설정
    SDL_SetRenderDrawColor(renderer, 0xDD, 0x8E, 0x40, 0xFF);
    SDL_RenderClear(renderer);
}

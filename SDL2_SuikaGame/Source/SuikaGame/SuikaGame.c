#include "SuikaGame.h"

void RenderBackground(SDL_Renderer* renderer, int screen_width, int screen_height)
{
    // 배경 채우기
    SDL_SetRenderDrawColor(renderer, 0xDD, 0x8E, 0x40, 0xFF);
    SDL_RenderClear(renderer);

    // 절반은 FFFEAA로
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFE, 0xAA, 0xFF);
    SDL_Rect half_rect = {
        .x = 0,
        .y = screen_height / 2 + (int)(screen_height * 0.1),
        .w = screen_width,
        .h = screen_height / 2,
    };
    SDL_RenderFillRect(renderer, &half_rect);
}

float GetScreenScale()
{
    // 화면 크기 가져오기
    SDL_DisplayMode DM;
    if (SDL_GetCurrentDisplayMode(0, &DM) != 0)
    {
        // 화면 크기 가져오기 실패시
        return 1.0f;
    }

    // 화면 크기와 비율에 맞게 스케일 조정
    return DM.w / 1920.0f;
}

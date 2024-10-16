#pragma once
#include <SDL.h>

/// @brief 창 생성 결과
typedef enum CreateWindowResult
{
    CREATE_WINDOW_SUCCESS,
    CREATE_WINDOW_FAIL_SDL_INIT,
    CREATE_WINDOW_FAIL_CREATE_WINDOW,
    CREATE_WINDOW_FAIL_CREATE_RENDERER,
} CreateWindowResult;

/// @brief 화면 정보
typedef struct View
{
    SDL_Window* window;
    SDL_Renderer* renderer;
} View;

/// @brief 화면 설정 빌더
typedef struct ScreenConfigBuilder
{
    int screen_x;
    int screen_y;
    int screen_width;
    int screen_height;
} ScreenConfigBuilder;

/// @brief ScreenConfigBuilder의 기본값을 반환합니다.
/// @return ScreenConfigBuilder의 기본값 { 0, 0, undefined, undefined }
ScreenConfigBuilder GetDefaultScreenConfigBuilder();

/// @brief 화면 생성 함수
/// @param view 화면 정보 구조체
/// @param title 창 이름
/// @param screen_config 화면 옵션 빌더
/// @return 초기화 성공 여부 (true: 성공, false: 실패)
CreateWindowResult CreateWindow(
    View* view,
    const char* title,
    const ScreenConfigBuilder* screen_config
);

/// @brief 화면 닫기
/// @param view 화면 정보 구조체
void CloseWindow(View* view);

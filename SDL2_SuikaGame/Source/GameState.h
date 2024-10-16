#pragma once

/// @brief 게임의 상태를 나타내는 열거형
typedef enum EGameState
{
    GameState_Exit,     // 게임 종료
    GameState_MainMenu, // 메인 메뉴
    GameState_Playing,  // 게임 플레이 중
    GameState_Pause,    // 일시 정지
    GameState_GameOver, // 게임 오버
} EGameState;

/// @brief 현재 게임의 상태를 나타내는 전역 변수
extern EGameState g_GameState;

#pragma once

/// @brief 프로그램의 상태를 나타내는 열거형
typedef enum EAppState
{
    AppState_Setup,
    AppState_MainMenu,
    AppState_Game,
    AppState_Exit,
} EAppState;

/// @brief 게임의 상태를 나타내는 열거형
typedef enum EGameState
{
    GameState_Setup,    // 게임 설정 중
    GameState_Playing,  // 게임 플레이 중
    GameState_Pause,    // 일시 정지
    GameState_GameOver, // 게임 오버
} EGameState;


/// @brief 현재 프로그램의 상태를 반환합니다.
/// @return 현재 프로그램의 상태
EAppState GetCurrentAppState();

/// @brief 프로그램의 상태를 설정합니다.
/// @param state 설정할 프로그램 상태
void SetCurrentAppState(EAppState state);


/// @brief 현재 게임의 상태를 반환합니다.
/// @return 현재 게임의 상태
EGameState GetCurrentGameState();

/// @brief 게임의 상태를 설정합니다.
/// @param state 설정할 게임 상태
void SetCurrentGameState(EGameState state);

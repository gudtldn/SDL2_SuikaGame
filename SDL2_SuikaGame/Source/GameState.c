#include "GameState.h"

// 프로그램 상태
g_AppState = AppState_Setup;

// 게임 상태
g_GameState = GameState_Setup;


// App관련
EAppState GetCurrentAppState()
{
    return g_AppState;
}

void SetCurrentAppState(EAppState state)
{
    g_AppState = state;
}

// Game관련
EGameState GetCurrentGameState()
{
    return g_GameState;
}

void SetCurrentGameState(EGameState state)
{
    g_GameState = state;
}

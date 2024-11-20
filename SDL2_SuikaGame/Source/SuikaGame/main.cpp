#include "EnginePCH.h"
#include "SuikaGame/Stages/MenuStage.h"
#include "SuikaGame/GameObjects/BackgroundObject.h"
#include "SuikaGame/GameObjects/BgmObject.h"

#include <windows.h>


// https://lazyfoo.net/tutorials/SDL/index.php
// https://www.youtube.com/watch?v=BDqJUJ-jOSQ
// https://box2d.org/documentation/hello.html
// https://wikidocs.net/book/6636

int main(int argc, char* args[])
{
#if _DEBUG
    // Debug 모드일 때 로그 레벨을 Debug로 설정
    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_DEBUG);
#endif

    try
    {
        // Engine 생성
        GameEngine engine = GameEngine{
            "Suika Game",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            SCREEN_WIDTH, SCREEN_HEIGHT
        };

        // Engine 실행
        engine.SetStage<MenuStage>();
        engine.GetObjectManager().CreateGameObject<BackgroundObject>();
        engine.GetObjectManager().CreateGameObject<BgmObject>();
        engine.Run();
    }
    catch (const std::exception& e)
    {
        LOG_ERROR("An error occurred: {}", e.what());

        // WCHAR 배열을 위한 버퍼
        WCHAR error_message[256];

        // e.what()에서 반환된 ANSI 문자열을 WCHAR로 변환
        MultiByteToWideChar(
            CP_UTF8,
            0,
            std::format("An error occurred: {}", e.what()).c_str(),
            -1,
            error_message,
            sizeof(error_message) / sizeof(WCHAR)
        );
        MessageBoxW(nullptr, error_message, L"Error", MB_OK | MB_ICONERROR);
        return -1;
    }

    return 0;
}

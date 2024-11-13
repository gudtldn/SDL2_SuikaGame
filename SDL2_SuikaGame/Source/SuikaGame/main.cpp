#include "EnginePCH.h"
#include "Stages/MenuStage.h"
#include "GameObjects/BackgroundObject.h"
#include "GameObjects/BgmObject.h"


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
        // SDL Manager 초기화
        std::unique_ptr<SDLManager> sdl_manager = std::make_unique<SDLManager>();

        // Screen Size 가져오기
        SDL_DisplayMode DM;
        SDL_GetCurrentDisplayMode(0, &DM);

        // Engine 생성
        std::unique_ptr<GameEngine> engine = std::make_unique<GameEngine>(
            "Suika Game",
            DM.w / 2 - SCREEN_WIDTH / 2,
            DM.h / 2 - SCREEN_HEIGHT / 2,
            SCREEN_WIDTH, SCREEN_HEIGHT
        );

        // Engine 실행
        engine->SetStage<MenuStage>();
        engine->GetObjectManager().CreateGameObject<BackgroundObject>();
        engine->GetObjectManager().CreateGameObject<BgmObject>();
        engine->Run();
    }
    catch (const std::exception& e)
    {
        LOG_ERROR("An error occurred: {}", e.what());
        return -1;
    }

    return 0;
}

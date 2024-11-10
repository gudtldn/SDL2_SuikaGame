#include "EngineCore.h"
#include "Menu/MenuStage.h"
#include "BgmObject.h"


// https://lazyfoo.net/tutorials/SDL/index.php
// https://www.youtube.com/watch?v=BDqJUJ-jOSQ
// https://box2d.org/documentation/hello.html
// https://wikidocs.net/book/6636

int main(int argc, char* args[])
{
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
        engine->GetObjectManager().AddGameObject<BgmObject>();
        engine->Run();
    }
    catch (const std::exception& e)
    {
        LOG_ERROR("An error occurred: %s", e.what());
        return -1;
    }

    return 0;
}

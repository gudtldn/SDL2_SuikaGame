#include "MenuStage.h"

#include "SuikaGame/MenuUIObjects/GameLogoObject.h"
#include "SuikaGame/MenuUIObjects/StartButtonObject.h"


MenuStage::MenuStage(GameEngine* engine)
    : Stage(engine)
{
}

void MenuStage::InitializeObjects()
{
    Stage::InitializeObjects();

    // 게임 로고 오브젝트 생성
    GetObjectManager().CreateGameObject<GameLogoObject>();

    // 시작 버튼 오브젝트 생성
    GetObjectManager().CreateGameObject<StartButtonObject>();
}

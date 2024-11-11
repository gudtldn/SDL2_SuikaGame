#include "MenuStage.h"
#include "StartButtonObject.h"
#include "GameLogoObject.h"


MenuStage::MenuStage(GameEngine* engine)
    : Stage(engine)
{
    // 게임 로고 오브젝트 생성
    GetObjectManager().CreateGameObject<GameLogoObject>();

    // 시작 버튼 오브젝트 생성
    GetObjectManager().CreateGameObject<StartButtonObject>();
}

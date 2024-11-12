#include "GameStage.h"

#include "SuikaGame/GameUIObjects/BorderObject.h"
#include "SuikaGame/GameUIObjects/BorderBackgroundObject.h"
#include "SuikaGame/GameUIObjects/ScoreboradObject.h"
#include "SuikaGame/GameObjects/PlayerObject.h"


GameStage::GameStage(GameEngine* engine)
    : Stage(engine)
{
    // BorderBackgroundObject 오브젝트 생성
    GetObjectManager().CreateGameObject<BorderBackgroundObject>();

    // BorderObject 오브젝트 생성
    GetObjectManager().CreateGameObject<BorderObject>();

    // ScoreboradObject 오브젝트 생성
    GetObjectManager().CreateGameObject<ScoreboradObject>();

    // PlayerObject 오브젝트 생성
    GetObjectManager().CreateGameObject<PlayerObject>();
}

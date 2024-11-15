#include "GameStage.h"

#include "SuikaGame/GameObjects/PlayerObject.h"
#include "SuikaGame/GameUIObjects/BorderObject.h"
#include "SuikaGame/GameUIObjects/BorderBackgroundObject.h"
#include "SuikaGame/GameUIObjects/ScoreboardObject.h"
#include "SuikaGame/GameResources/FruitResourceObject.h"


GameStage::GameStage(GameEngine* engine)
    : Stage(engine)
{
    ObjectManager& obj_manager = GetObjectManager();

    // FruitsResourceObject 오브젝트 생성
    obj_manager.CreateGameObject<FruitResourceObject>();

    // BorderBackgroundObject 오브젝트 생성
    obj_manager.CreateGameObject<BorderBackgroundObject>();

    // BorderObject 오브젝트 생성
    obj_manager.CreateGameObject<BorderObject>();

    // ScoreboardObject 오브젝트 생성
    obj_manager.CreateGameObject<ScoreboardObject>();

    // PlayerObject 오브젝트 생성
    obj_manager.CreateGameObject<PlayerObject>();
}

#include "GameStage.h"

#include "SuikaGame/GameObjects/PlayerObject.h"
#include "SuikaGame/GameObjects/BorderObject.h"
#include "SuikaGame/GameUIObjects/BorderBackgroundObject.h"
#include "SuikaGame/GameUIObjects/ScoreboardObject.h"
#include "SuikaGame/GameUIObjects/NextFruitDisplayObject.h"
#include "SuikaGame/GameResources/FruitResourceObject.h"


GameStage::GameStage(GameEngine* engine)
    : Stage(engine)
{
}

void GameStage::InitializeObjects()
{
    Stage::InitializeObjects();
    ObjectManager& obj_manager = GetObjectManager();

    // FruitsResourceObject 오브젝트 생성
    obj_manager.CreateGameObject<FruitResourceObject>();

    // BorderBackgroundObject 오브젝트 생성
    obj_manager.CreateGameObject<BorderBackgroundObject>();

    // BorderObject 오브젝트 생성
    obj_manager.CreateGameObject<BorderObject>();

    // ScoreboardObject 오브젝트 생성
    obj_manager.CreateGameObject<ScoreboardObject>();

    // NextFruitDisplayObject 오브젝트 생성
    obj_manager.CreateGameObject<NextFruitDisplayObject>();

    // PlayerObject 오브젝트 생성
    obj_manager.CreateGameObject<PlayerObject>();
}

void GameStage::HandleFixedUpdate(float fixed_time)
{
    Stage::HandleFixedUpdate(fixed_time);

    // Box2D Contact Event
    const b2ContactEvents contact_events = b2World_GetContactEvents(box2d_manager.GetWorldID());

    // BeginOverlap Event
    for (int i = 0; i < contact_events.beginCount; ++i)
    {
        const b2ContactBeginTouchEvent* begin_event = contact_events.beginEvents + i;
        box2d_manager.OnBeginOverlap.Broadcast(
            static_cast<GameObject*>(b2Shape_GetUserData(begin_event->shapeIdA)),
            static_cast<GameObject*>(b2Shape_GetUserData(begin_event->shapeIdB))
        );
    }

    // EndOverlap Event
    for (int i = 0; i < contact_events.endCount; ++i)
    {
        const b2ContactEndTouchEvent* end_event = contact_events.endEvents + i;
        box2d_manager.OnEndOverlap.Broadcast(
            static_cast<GameObject*>(b2Shape_GetUserData(end_event->shapeIdA)),
            static_cast<GameObject*>(b2Shape_GetUserData(end_event->shapeIdB))
        );
    }

    // Hit Event
    for (int i = 0; i < contact_events.hitCount; ++i)
    {
        const b2ContactHitEvent* hit_event = contact_events.hitEvents + i;
        box2d_manager.OnBeginOverlap.Broadcast(
            static_cast<GameObject*>(b2Shape_GetUserData(hit_event->shapeIdA)),
            static_cast<GameObject*>(b2Shape_GetUserData(hit_event->shapeIdB))
        );
    }

    // 물리 시뮬레이션
    box2d_manager.Step(fixed_time * 4, 8);
}

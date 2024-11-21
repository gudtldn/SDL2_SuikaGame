#include "GameStage.h"

#include "SuikaGame/GameObjects/PlayerObject.h"
#include "SuikaGame/GameObjects/BorderObject.h"
#include "SuikaGame/GameUIObjects/BorderBackgroundObject.h"
#include "SuikaGame/GameUIObjects/ScoreboardObject.h"
#include "SuikaGame/GameUIObjects/NextFruitDisplayObject.h"
#include "SuikaGame/GameUIObjects/CircleOfEvolutionDisplayObject.h"
#include "SuikaGame/GameResources/FruitResourceObject.h"


GameStage::GameStage(GameEngine* engine)
    : Stage(engine)
    , is_game_over(false)
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

    // CircleOfEvolutionDisplayObject 오브젝트 생성
    obj_manager.CreateGameObject<CircleOfEvolutionDisplayObject>();

    // PlayerObject 오브젝트 생성
    obj_manager.CreateGameObject<PlayerObject>();
}

void GameStage::HandleUpdate(float delta_time)
{
    Stage::HandleUpdate(delta_time);
    // TODO: 게임 오버 처리
}

void GameStage::HandleFixedUpdate(float fixed_time)
{
    Stage::HandleFixedUpdate(fixed_time);
    if (is_game_over) return; // TODO: 게임 오버 처리

    // Box2D Sensor Event
    const b2SensorEvents sensor_events = b2World_GetSensorEvents(box2d_manager.GetWorldID());

    // BeginSensorOverlap Event
    for (int i = 0; i < sensor_events.beginCount; ++i)
    {
        const b2SensorBeginTouchEvent* begin_touch = sensor_events.beginEvents + i;
        box2d_manager.OnBeginSensorOverlap.Broadcast(
            static_cast<GameObject*>(b2Shape_GetUserData(begin_touch->visitorShapeId))
        );
    }

    // EndSensorOverlap Event
    for (int i = 0; i < sensor_events.endCount; ++i)
    {
        const b2SensorEndTouchEvent* end_touch = sensor_events.endEvents + i;
        box2d_manager.OnEndSensorOverlap.Broadcast(
            static_cast<GameObject*>(b2Shape_GetUserData(end_touch->visitorShapeId))
        );
    }


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

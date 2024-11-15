#include "Box2DManager.h"


Box2DManager::Box2DManager()
{
    // Box2D 월드 정의
    b2WorldDef world_def = b2DefaultWorldDef();
    world_def.gravity = b2Vec2{0.0f, 9.8f * 15.0f};

    // 월드 생성
    world_id = b2CreateWorld(&world_def);
}

Box2DManager::~Box2DManager()
{
    b2DestroyWorld(world_id);
}

void Box2DManager::Step(float time_step, int sub_step_count) const
{
    b2World_Step(world_id, time_step, sub_step_count);
}

inline Vector2D Box2DManager::GetGravity() const
{
    auto [x, y] = b2World_GetGravity(world_id);
    return { x, y };
}

inline void Box2DManager::SetGravity(Vector2D gravity) const
{
    b2World_SetGravity(world_id, { gravity.X, gravity.Y });
}

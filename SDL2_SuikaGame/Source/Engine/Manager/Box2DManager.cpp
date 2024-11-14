#include "Box2DManager.h"


Box2DManager::Box2DManager()
{
    // Box2D 월드 정의
    b2WorldDef world_def = b2DefaultWorldDef();
    world_def.gravity = b2Vec2{0.0f, -9.8f};

    // 월드 생성
    world_id = b2CreateWorld(&world_def);
}

Box2DManager::~Box2DManager()
{
    b2DestroyWorld(world_id);
}

inline Vector2D Box2DManager::GetGravity() const
{
    b2Vec2 gravity = b2World_GetGravity(world_id);
    return { gravity.x, gravity.y };
}

inline void Box2DManager::SetGravity(Vector2D gravity) const
{
    b2World_SetGravity(world_id, { gravity.X, gravity.Y });
}

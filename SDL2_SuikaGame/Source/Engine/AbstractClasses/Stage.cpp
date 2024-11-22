#include "Stage.h"
#include "Engine/GameEngine.h"


Stage::Stage(GameEngine* engine)
    : engine(engine)
    , object_manager(engine)
{
}

void Stage::InitializeStage()
{
}

void Stage::HandleEvent(const SDL_Event& event)
{
    object_manager.HandleEvent(event);
}

void Stage::HandleUpdate(float delta_time)
{
    object_manager.HandleUpdate(delta_time);
}

void Stage::HandleFixedUpdate(float fixed_time)
{
    object_manager.HandleFixedUpdate(fixed_time);
}

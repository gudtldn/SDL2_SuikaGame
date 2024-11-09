#include "Stage.h"
#include "GameObject.h"


void Stage::Update(double delta_time)
{
    for (auto& game_object : game_objects)
    {
        game_object->Update(delta_time);
    }
}

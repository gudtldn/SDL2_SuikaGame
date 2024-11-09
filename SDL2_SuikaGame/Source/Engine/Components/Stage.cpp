#include "Stage.h"
#include "GameObject.h"


void Stage::Update(double delta_time)
{
    for (const auto& new_game_object : new_game_objects)
    {
        new_game_object->BeginPlay();
    }
    new_game_objects.clear();

    for (auto& game_object : game_objects)
    {
        game_object->Update(delta_time);
    }
}

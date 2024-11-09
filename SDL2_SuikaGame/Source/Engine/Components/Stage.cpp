#include "Stage.h"
#include "GameObject.h"


void Stage::Update(double delta_time)
{
    // 게임 오브젝트 업데이트
    for (auto& game_object : game_objects)
    {
        game_object->Update(delta_time);
    }
}

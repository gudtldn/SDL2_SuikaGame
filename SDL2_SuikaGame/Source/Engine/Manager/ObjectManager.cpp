#include "ObjectManager.h"
#include "Components/GameObject.h"


void ObjectManager::Update(double delta_time)
{
    for (auto& object : game_objects)
    {
        object->Update(delta_time);
    }
}

void ObjectManager::Render()
{
    for (auto& object : game_objects)
    {
        object->Render();
    }
}

// AddGameObject는 template함수로 .h 파일에 정의되어 있습니다.
// void ObjectManager::AddGameObject(std::shared_ptr<GameObject> object) {}

void ObjectManager::RemoveGameObject(std::shared_ptr<GameObject> object)
{
    game_objects.erase(object);
}

void ObjectManager::Clear()
{
    game_objects.clear();
}

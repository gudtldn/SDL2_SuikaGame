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

void ObjectManager::RemoveGameObject(std::shared_ptr<GameObject> object)
{
    game_objects.erase(object);
}

void ObjectManager::Clear()
{
    game_objects.clear();
}

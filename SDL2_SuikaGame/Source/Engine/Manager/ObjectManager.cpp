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

template <typename Obj>
    requires std::derived_from<Obj, GameObject>
void ObjectManager::AddGameObject()
{
    auto object = std::make_shared<Obj>();
    game_objects.insert(object);
}

void ObjectManager::RemoveGameObject(std::shared_ptr<GameObject> object)
{
    game_objects.erase(object);
}

void ObjectManager::Clear()
{
    game_objects.clear();
}

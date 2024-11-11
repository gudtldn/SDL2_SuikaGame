#include "ObjectManager.h"
#include "Components/GameObject.h"


void ObjectManager::HandleEvent(const SDL_Event& event)
{
    for (auto& object : game_objects)
    {
        object->OnEvent(event);
    }
}

void ObjectManager::Update(double delta_time)
{
    for (auto& object : game_objects)
    {
        object->Update(delta_time);
    }
}

// CreateGameObject는 template함수로 .h 파일에 정의되어 있습니다.
// template <typename Obj>
//     requires std::derived_from<Obj, GameObject>
// Obj* ObjectManager::CreateGameObject() {}

void ObjectManager::DestroyGameObject(std::shared_ptr<GameObject> object)
{
    // object가 존재하지 않으면 return
    if (!object) return;

    game_objects.erase(object);
}

void ObjectManager::RemoveAllGameObjects()
{
    game_objects.clear();
}

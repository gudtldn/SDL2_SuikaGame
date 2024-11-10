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

void ObjectManager::Render(SDL_Renderer* renderer)
{
    for (auto& object : game_objects)
    {
        object->Render(renderer);
    }
}

// CreateGameObject는 template함수로 .h 파일에 정의되어 있습니다.
// Obj* ObjectManager::CreateGameObject()

void ObjectManager::DestroyGameObject(std::shared_ptr<GameObject> object)
{
    game_objects.erase(object);
}

void ObjectManager::Clear()
{
    game_objects.clear();
}

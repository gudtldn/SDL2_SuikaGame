#include "ObjectManager.h"
#include "Engine/AbstractClasses/GameObject.h"

#include <algorithm>


void ObjectManager::HandleEvent(const SDL_Event& event)
{
    const auto copy_game_objects = game_objects;
    for (auto& object : copy_game_objects)
    {
        object->OnEvent(event);
    }
}

void ObjectManager::HandleUpdate(float delta_time)
{
    const auto copy_game_objects = game_objects;
    for (auto& object : copy_game_objects)
    {
        object->Update(delta_time);
    }
}

void ObjectManager::HandleFixedUpdate(float fixed_time)
{
    const auto copy_game_objects = game_objects;
    for (auto& object : copy_game_objects)
    {
        object->FixedUpdate(fixed_time);
    }
}

// CreateGameObject는 template함수로 .h 파일에 정의되어 있습니다.
// template <typename Obj>
//     requires std::derived_from<Obj, GameObject>
// Obj* ObjectManager::CreateGameObject() {}

void ObjectManager::DestroyGameObject(const std::shared_ptr<GameObject>& object)
{
    // object가 존재하지 않으면 return
    if (!object) return;

    if (game_objects.erase(object) > 0)
    {
        pending_destroy_objects.push(object);
    }
}

void ObjectManager::RemoveAllGameObjects()
{
    for (const auto& object : game_objects)
    {
        pending_destroy_objects.push(object);
    }
    game_objects.clear();
}

void ObjectManager::ProcessPendingDestroyObjects()
{
    while (!pending_destroy_objects.empty())
    {
        const auto object = pending_destroy_objects.front();
        pending_destroy_objects.pop();

        // 완전히 삭제하기 전에 OnDestroy()를 호출
        object->OnDestroy();
    }
}

void ObjectManager::GetGameObjectsByTag(const std::string& tag, std::vector<GameObject*>& out_objects) const
{
    for (const auto& object : game_objects)
    {
        if (object->GetTags().contains(tag))
        {
            out_objects.push_back(object.get());
        }
    }        
}

void ObjectManager::GetGameObjectsByTags(
    const std::unordered_set<std::string>& tags,
    std::vector<GameObject*>& out_objects
) const {
    for (const auto& object : game_objects)
    {
        const auto& object_tags = object->GetTags();
        if (std::ranges::includes(object_tags, tags))
        {
            out_objects.push_back(object.get());
        }
    }
}

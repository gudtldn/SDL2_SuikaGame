#include "ObjectManager.h"
#include "Engine/Components/GameObject.h"

#include <algorithm>


void ObjectManager::HandleEvent(const SDL_Event& event)
{
    auto copy_game_objects = game_objects;
    for (auto& object : copy_game_objects)
    {
        object->OnEvent(event);
    }
}

void ObjectManager::HandleUpdate(float delta_time)
{
    auto copy_game_objects = game_objects;
    for (auto& object : copy_game_objects)
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

    // 완전히 삭제하기 전에 OnDestroy()를 호출
    object->OnDestroy();

    // TODO: 추후에 지연 삭제 기능 추가
    // https://www.perplexity.ai/search/igeon-jeogjeolhage-jal-sagjeha-hQZ4F0llSH.ZFqhWgJ..SQ
    game_objects.erase(object);
}

void ObjectManager::RemoveAllGameObjects()
{
    game_objects.clear();
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
        if (std::includes(
            object_tags.begin(), object_tags.end(),
            tags.begin(), tags.end()
        ))
        {
            out_objects.push_back(object.get());
        }
    }
}

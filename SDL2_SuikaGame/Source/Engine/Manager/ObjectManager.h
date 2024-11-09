#pragma once
#include <memory>
#include <type_traits>
#include <vector>
#include <unordered_set>

// forward declaration
class GameObject;


/// @brief 게임 오브젝트를 관리하는 매니저 클래스
class ObjectManager
{
protected:
    /// @brief 게임 오브젝트를 담을 집합
    std::unordered_set<std::shared_ptr<GameObject>> game_objects;

    /// @brief 새로운 게임 오브젝트의 벡터
    std::vector<std::shared_ptr<GameObject>> new_game_objects;

public:
    ObjectManager() = default;
    ~ObjectManager() = default;

    /// @brief 게임 오브젝트를 업데이트합니다.
    /// @param delta_time Delta time
    virtual void Update(double delta_time);

    /// @brief 게임 오브젝트를 렌더링합니다.
    virtual void Render();

    /// @brief 게임 오브젝트를 추가합니다.
    /// @tparam GameObject를 상속받은 클래스
    template <typename Obj>
        requires std::derived_from<Obj, GameObject>
    void AddGameObject();

    /// @brief 게임 오브젝트를 제거합니다.
    /// @param object 제거할 게임 오브젝트
    virtual void RemoveGameObject(std::shared_ptr<GameObject> object);

    /// @brief 모든 게임 오브젝트를 제거합니다.
    virtual void Clear();
};


template <typename Obj>
    requires std::derived_from<Obj, GameObject>
void ObjectManager::AddGameObject()
{
    auto object = std::make_shared<Obj>();
    game_objects.insert(object);
    new_game_objects.push_back(object);
}

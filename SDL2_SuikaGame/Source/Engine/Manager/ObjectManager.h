#pragma once
#include <memory>
#include <type_traits>
#include <unordered_set>

// forward declaration
class GameObject;


/// @brief 게임 오브젝트를 관리하는 매니저 클래스
class ObjectManager
{
protected:
    /// @brief 게임 오브젝트를 담을 집합
    std::unordered_set<std::shared_ptr<GameObject>> game_objects;

public:
    ObjectManager() = default;
    ~ObjectManager() = default;

    /// @brief 게임 오브젝트를 업데이트합니다.
    virtual void Update(double delta_time);

    /// @brief 게임 오브젝트를 렌더링합니다.
    virtual void Render();

    /// @brief 게임 오브젝트를 추가합니다.
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
inline void ObjectManager::AddGameObject()
{
    auto object = std::make_shared<Obj>();
    game_objects.insert(object);
}

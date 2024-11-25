#pragma once
#include <memory>
#include <string>
#include <queue>
#include <vector>
#include <concepts>
#include <unordered_set>

// forward declaration
class GameEngine;
class GameObject;
struct SDL_Renderer;
union SDL_Event;


/// @brief 게임 오브젝트를 관리하는 매니저 클래스
class ObjectManager
{
private:
    /// @brief 게임 엔진
    GameEngine* engine;

    /// @brief 게임 오브젝트를 담을 집합
    std::unordered_set<std::shared_ptr<GameObject>> game_objects;

    /// @brief 게임 오브젝트 제거 대기열
    std::queue<std::shared_ptr<GameObject>> pending_destroy_objects;

    /// @brief 새로운 게임 오브젝트의 대기열
    std::queue<std::weak_ptr<GameObject>> new_game_objects;

public:
    ObjectManager(GameEngine* engine)
        : engine(engine) {}

    virtual ~ObjectManager() = default;

    // 복사 & 이동 생성자 제거
    ObjectManager(const ObjectManager&) = delete;
    ObjectManager& operator=(const ObjectManager&) = delete;
    ObjectManager(ObjectManager&&) = delete;
    ObjectManager& operator=(ObjectManager&&) = delete;

    
    /// @brief SDL 이벤트 발생 시 호출됩니다.
    /// @param event SDL 이벤트
    virtual void HandleEvent(const SDL_Event& event);

    /// @brief 게임 오브젝트를 업데이트합니다.
    /// @param delta_time Delta time
    virtual void HandleUpdate(float delta_time);

    /// @brief 고정된 시간만큼 게임 오브젝트를 업데이트합니다.
    /// @param fixed_time 고정된 시간
    virtual void HandleFixedUpdate(float fixed_time);

    /// @brief 게임 오브젝트를 추가합니다.
    /// @tparam Obj GameObject를 상속받은 클래스
    template <typename Obj>
        requires std::derived_from<Obj, GameObject>
    Obj* CreateGameObject();

    /// @brief 새로운 게임 오브젝트들의 BeginPlay를 호출합니다.
    virtual void InitializeNewGameObjects();

    /// @brief 게임 오브젝트를 제거합니다.
    /// @param object 제거할 게임 오브젝트
    virtual void DestroyGameObject(const std::shared_ptr<GameObject>& object);

    /// @brief 모든 게임 오브젝트를 제거합니다.
    virtual void RemoveAllGameObjects();

    /// @brief 제거 대기열에 있는 게임 오브젝트를 처리합니다.
    virtual void ProcessPendingDestroyObjects();

    /// @brief 게임 오브젝트를 가져옵니다.
    /// @tparam T GameObject를 상속받은 클래스
    /// @param out_objects 게임 오브젝트를 담을 벡터
    template <typename T>
        requires std::derived_from<T, GameObject>
    void GetGameObjectsOfClass(std::vector<T*>& out_objects) const;

    /// @brief 태그로 게임 오브젝트를 가져옵니다.
    /// @param tag 태그
    /// @param out_objects 게임 오브젝트를 담을 벡터
    void GetGameObjectsByTag(const std::string& tag, std::vector<GameObject*>& out_objects) const;

    /// @brief 여러 태그로 게임 오브젝트를 가져옵니다.
    /// @param tags 태그들
    /// @param out_objects 게임 오브젝트를 담을 벡터
    void GetGameObjectsByTags(const std::unordered_set<std::string>& tags, std::vector<GameObject*>& out_objects) const;

    /****** Getter & Setter ******/

    /// @brief 게임 오브젝트를 가져옵니다.
    [[nodiscard]] const auto& GetGameObjects() const { return game_objects; }
};


template <typename Obj>
    requires std::derived_from<Obj, GameObject>
Obj* ObjectManager::CreateGameObject()
{
    auto object = std::make_shared<Obj>(engine);

    // 게임 오브젝트를 관리하는 컨테이너에 추가
    game_objects.insert(object);
    new_game_objects.emplace(object);

    return object.get();
}

template <typename T>
    requires std::derived_from<T, GameObject>
void ObjectManager::GetGameObjectsOfClass(std::vector<T*>& out_objects) const
{
    for (const auto& object : game_objects)
    {
        if (auto casted_object = std::dynamic_pointer_cast<T>(object))
        {
            out_objects.push_back(casted_object.get());
        }
    }
}

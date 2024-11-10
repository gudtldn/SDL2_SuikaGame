#pragma once
#include <memory>
#include <type_traits>
#include <vector>
#include <unordered_set>

// forward declaration
class GameEngine;
class GameObject;
class IEventObserver;
struct SDL_Renderer;


/// @brief 게임 오브젝트를 관리하는 매니저 클래스
class ObjectManager
{
private:
    /// @brief 게임 엔진
    GameEngine* engine;

protected:
    /// @brief 게임 오브젝트를 담을 집합
    std::unordered_set<std::shared_ptr<GameObject>> game_objects;

    /// @brief 새로운 게임 오브젝트의 벡터
    std::vector<std::shared_ptr<GameObject>> new_game_objects;

    /// @brief 이벤트 옵저버 목록
    std::vector<std::shared_ptr<IEventObserver>> new_event_observers;


public:
    ObjectManager(GameEngine* engine)
        : engine(engine) {};

    ~ObjectManager() = default;

    /// @brief 게임 오브젝트를 업데이트합니다.
    /// @param delta_time Delta time
    virtual void Update(double delta_time);

    /// @brief 게임 오브젝트를 렌더링합니다.
    virtual void Render(SDL_Renderer* renderer);

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


    /****** Getter & Setter ******/

    /// @brief 게임 오브젝트를 가져옵니다.
    auto& GetGameObjects() const { return game_objects; }

    /// @brief 새롭게 추가된 게임 오브젝트 목록을 가져옵니다.
    auto& GetNewGameObjects() const { return new_game_objects; }

    /// @brief 새롭게 추가된 게임 오브젝트 목록을 제거합니다.
    void ClearNewGameObjects() { new_game_objects.clear(); }

    /// @brief 새롭게 추가된 이벤트 옵저버 목록을 가져옵니다.
    auto& GetNewEventObservers() const { return new_event_observers; }

    /// @brief 새롭게 추가된 이벤트 옵저버 목록을 제거합니다.
    void ClearNewEventObservers() { new_event_observers.clear(); }
};


template <typename Obj>
    requires std::derived_from<Obj, GameObject>
void ObjectManager::AddGameObject()
{
    auto object = std::make_shared<Obj>(engine);

    // 게임 오브젝트를 관리하는 컨테이너에 추가
    game_objects.insert(object);
    new_game_objects.push_back(object);

    // 이벤트 옵저버가 구현되어 있는 경우 추가
    if constexpr (std::is_base_of_v<IEventObserver, Obj>)
    {
        new_event_observers.push_back(object);
    }
}

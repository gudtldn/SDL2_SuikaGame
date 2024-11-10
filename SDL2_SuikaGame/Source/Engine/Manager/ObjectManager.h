#pragma once
#include <memory>
#include <type_traits>
#include <vector>
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

protected:
    /// @brief 게임 오브젝트를 담을 집합
    std::unordered_set<std::shared_ptr<GameObject>> game_objects;

    /// @brief 새로운 게임 오브젝트의 벡터
    std::vector<GameObject*> new_game_objects;


public:
    ObjectManager(GameEngine* engine)
        : engine(engine) {};

    ~ObjectManager() = default;

    /// @brief SDL 이벤트 발생 시 호출됩니다.
    /// @param event SDL 이벤트
    virtual void HandleEvent(const SDL_Event& event);

    /// @brief 게임 오브젝트를 업데이트합니다.
    /// @param delta_time Delta time
    virtual void Update(double delta_time);

    /// @brief 게임 오브젝트를 렌더링합니다.
    virtual void Render(SDL_Renderer* renderer);

    /// @brief 게임 오브젝트를 추가합니다.
    /// @tparam GameObject를 상속받은 클래스
    template <typename Obj>
        requires std::derived_from<Obj, GameObject>
    Obj* CreateGameObject();

    /// @brief 게임 오브젝트를 제거합니다.
    /// @param object 제거할 게임 오브젝트
    virtual void DestroyGameObject(std::shared_ptr<GameObject> object);

    /// @brief 모든 게임 오브젝트를 제거합니다.
    virtual void Clear();


    /****** Getter & Setter ******/

    /// @brief 게임 오브젝트를 가져옵니다.
    auto& GetGameObjects() const { return game_objects; }

    /// @brief 새롭게 추가된 게임 오브젝트 목록을 가져옵니다.
    auto& GetNewGameObjects() const { return new_game_objects; }

    /// @brief 새롭게 추가된 게임 오브젝트 목록을 제거합니다.
    void ClearNewGameObjects() { new_game_objects.clear(); }
};


template <typename Obj>
    requires std::derived_from<Obj, GameObject>
Obj* ObjectManager::CreateGameObject()
{
    auto object = std::make_shared<Obj>(engine);
    Obj* raw_pointer = object.get();

    // 게임 오브젝트를 관리하는 컨테이너에 추가
    game_objects.insert(object);
    new_game_objects.push_back(raw_pointer);

    return raw_pointer;
}

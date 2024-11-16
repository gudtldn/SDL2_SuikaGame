#pragma once
#include <memory>

#include <string>
#include <unordered_map>
#include <unordered_set>

// forward declaration
class Stage;
class GameEngine;
struct SDL_Renderer;
union SDL_Event;


/// @brief 게임 오브젝트 클래스
class GameObject : public std::enable_shared_from_this<GameObject>
{
private:
    /// @brief 게임 엔진
    GameEngine* engine;

    /// @brief 인스턴스 카운트
    static std::unordered_map<std::string, int> instance_id;

protected:
    /// @brief 게임 오브젝트의 z-order
    int z_order = 0;

    /// @brief GameObject의 Tags
    std::unordered_set<std::string> tags;

public:
    GameObject(GameEngine* engine)
        : engine(engine) { instance_id[typeid(*this).raw_name()]++; }

    virtual ~GameObject() = default;

    // 복사 & 이동 생성자 제거
    GameObject(const GameObject&) = delete;
    GameObject& operator=(const GameObject&) = delete;
    GameObject(GameObject&&) = delete;
    GameObject& operator=(GameObject&&) = delete;


    /****** Virtual Functions ******/

    /// @brief 생성이 되었을 때 호출됩니다.
    virtual void BeginPlay();

    /// @brief 매 프레임마다 호출됩니다.
    virtual void Update(float delta_time);

    /// @brief 고정된 시간마다 호출됩니다.
    virtual void FixedUpdate(float fixed_time);

    /// @brief 게임 오브젝트가 렌더링될 때 호출됩니다.
    virtual void Render(SDL_Renderer* renderer) const;

    /// @brief 게임 오브젝트가 파괴되기 직전에 호출됩니다.
    virtual void OnDestroy();

    /// @brief 이벤트가 발생했을 때 호출됩니다.
    virtual void OnEvent(const SDL_Event& event);

    /// @brief 게임 오브젝트의 이름을 가져옵니다.
    /// @return 게임 오브젝트의 이름
    virtual std::string GetName() const;


    /****** Methods ******/

    /// @brief 게임 오브젝트를 파괴합니다.
    void Destroy();


    /****** Getter & Setter ******/

    /// @brief z-order를 가져옵니다.
    inline int GetZOrder() const { return z_order; }

    /// @brief z-order를 설정합니다.
    inline void SetZOrder(int new_z_order) { z_order = new_z_order; }

    /// @brief 태그를 가져옵니다.
    inline const std::unordered_set<std::string>& GetTags() const { return tags; }

    /// @brief 태그를 추가합니다.
    void AddTag(const std::string& tag) { tags.insert(tag); }

    /// @brief 태그를 제거합니다.
    void RemoveTag(const std::string& tag) { tags.erase(tag); }

    /// @brief 게임 엔진을 가져옵니다.
    inline GameEngine* GetEngine() const { return engine; }

    /// @brief 현재 스테이지를 가져옵니다.
    inline Stage* GetCurrentStage() const;
};

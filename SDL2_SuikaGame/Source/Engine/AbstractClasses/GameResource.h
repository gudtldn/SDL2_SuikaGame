#pragma once

// forward declaration
class GameEngine;


/// @brief 게임 리소스를 나타내는 추상 클래스
class GameResource
{
protected:
    GameEngine* engine = nullptr;

public:
    virtual ~GameResource() = default;

    /// @brief 리소스를 로드 및, 초기화합니다.
    virtual void Load() = 0;

private:
    void SetEngine(GameEngine* in_engine) { engine = in_engine; }

    // ResourceManager를 friend로 지정
    friend class ResourceManager;
};

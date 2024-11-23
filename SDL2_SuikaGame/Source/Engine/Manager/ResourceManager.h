#pragma once
#include <memory>
#include <typeindex>
#include <type_traits>
#include <unordered_map>
#include "Engine/AbstractClasses/GameResource.h"
#include "Engine/Utils/LogMacros.h"

// forward declaration
class GameEngine;


/// @brief 게임 리소스를 관리하는 클래스
class ResourceManager
{
    /// @brief 엔진 객체
    GameEngine* engine;

    /// @brief 게임 리소스를 담을 map
    std::unordered_map<std::type_index, std::unique_ptr<GameResource>> resources;

public:
    explicit ResourceManager(GameEngine* engine)
        : engine(engine) {}

    /// @brief 게임 리소스를 추가합니다.
    /// @tparam Res GameResource를 상속받은 클래스
    template <typename Res>
        requires std::is_base_of_v<GameResource, Res>
    void AddResource();

    /// @brief 게임 리소스를 가져옵니다.
    /// @tparam Res GameResource를 상속받은 클래스
    /// @return Res* 리소스 포인터
    template <typename Res>
        requires std::is_base_of_v<GameResource, Res>
    Res* GetResource() const;
};


template <typename Res>
    requires std::is_base_of_v<GameResource, Res>
void ResourceManager::AddResource()
{
    std::unique_ptr<Res> resource = std::make_unique<Res>();
    resource->SetEngine(engine);
    resource->Load();

    auto [it, inserted] = resources.emplace(
        std::type_index(typeid(Res)),
        std::move(resource)
    );

#ifdef _DEBUG
    if (!inserted)
    {
        LOG_ERROR("Resource already exists!");
        throw std::runtime_error("Resource already exists!");
    }
#endif
}

template <typename Res>
    requires std::is_base_of_v<GameResource, Res>
Res* ResourceManager::GetResource() const
{
    return static_cast<Res*>(
        resources.at(std::type_index(typeid(Res))).get()
    );
}

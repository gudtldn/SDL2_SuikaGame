#include "GameObject.h"
#include "GameEngine.h"
#include "Stage.h"
#include <format>


std::unordered_map<std::string, int32_t> GameObject::instance_id;

void GameObject::BeginPlay()
{
}

void GameObject::Update(double delta_time)
{
}

void GameObject::Render(SDL_Renderer* renderer)
{
}

void GameObject::OnDestory()
{
}

void GameObject::OnEvent(const SDL_Event& event)
{
}

std::string GameObject::GetName() const
{
    std::string name = typeid(*this).name();

    return std::format(
        "{}_Inst{}",
        name,
        instance_id[name]++
    );
}

void GameObject::Destroy()
{
    auto self = shared_from_this();

    // 오브젝트 매니저에서 제거
    GetCurrentStage()->GetObjectManager().DestroyGameObject(self);
    GetEngine()->GetObjectManager().DestroyGameObject(self);
}

inline Stage* GameObject::GetCurrentStage() const
{
    return engine->GetCurrentStage();
}

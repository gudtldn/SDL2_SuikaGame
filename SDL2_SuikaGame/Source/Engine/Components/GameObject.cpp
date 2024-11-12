#include "GameObject.h"

#include "Engine/GameEngine.h"
#include "Engine/Components/Stage.h"

#include <format>


std::unordered_map<std::string, int> GameObject::instance_id;

void GameObject::BeginPlay()
{
}

void GameObject::Update(float delta_time)
{
}

void GameObject::Render(SDL_Renderer* renderer) const
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
        "{}_Inst_{}",
        name.substr(name.find_first_of(' ') + 1),
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

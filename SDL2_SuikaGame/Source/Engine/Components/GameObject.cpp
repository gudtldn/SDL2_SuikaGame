#include "GameObject.h"
#include "GameEngine.h"
#include "Stage.h"


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

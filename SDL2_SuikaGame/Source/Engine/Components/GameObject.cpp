#include "GameObject.h"

#include "Engine/GameEngine.h"
#include "Engine/Components/Stage.h"


void GameObject::BeginPlay()
{
}

void GameObject::Update(float delta_time)
{
}

void GameObject::FixedUpdate(float fixed_time)
{
}

void GameObject::Render(SDL_Renderer* renderer) const
{
}

void GameObject::OnDestroy()
{
}

void GameObject::OnEvent(const SDL_Event& event)
{
}

void GameObject::Destroy()
{
    const auto self = shared_from_this();

    // 오브젝트 매니저에서 제거
    if (GetCurrentStage()->GetObjectManager().GetGameObjects().contains(self))
    {
        GetCurrentStage()->GetObjectManager().DestroyGameObject(self);
    }
    else
    {
        GetEngine()->GetObjectManager().DestroyGameObject(self);
    }
}

inline Stage* GameObject::GetCurrentStage() const
{
    return engine->GetCurrentStage();
}

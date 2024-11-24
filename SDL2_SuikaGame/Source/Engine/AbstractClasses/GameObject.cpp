#include "GameObject.h"

#include "Engine/GameEngine.h"
#include "Engine/AbstractClasses/Stage.h"


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
    if (GetEngine()->GetObjectManager().GetGameObjects().contains(self))
    {
        GetEngine()->GetObjectManager().DestroyGameObject(self);
    }
    else
    {
        GetCurrentStage()->GetObjectManager().DestroyGameObject(self);
    }

    // 오브젝트 무효화
    is_valid = false;
}

inline Stage* GameObject::GetCurrentStage() const
{
    return engine->GetCurrentStage();
}

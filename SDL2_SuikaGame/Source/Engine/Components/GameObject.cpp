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
}

inline Stage* GameObject::GetCurrentStage() const
{
    return engine->GetCurrentStage();
}

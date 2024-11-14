#pragma once
#include "EnginePCH.h"

class FruitResourceObject;


/// @brief 과일 오브젝트
class FruitObject : public GameObject
{
    FruitResourceObject* fruit_resource_object;
    const Texture2D* fruit_texture;

public:
    FruitObject(GameEngine* engine);

protected:
    virtual void BeginPlay() override;
    virtual void Update(float delta_time) override;
    virtual void Render(SDL_Renderer* renderer) const override;
};

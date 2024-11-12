#pragma once
#include "EnginePCH.h"


/// @brief BorderObject 클래스
class BorderObject : public GameObject
{
private:
    std::unique_ptr<Texture> border_texture;

public:
    BorderObject(GameEngine* engine);

    virtual void Update(float delta_time) override;
    virtual void Render(SDL_Renderer* renderer) const override;
};

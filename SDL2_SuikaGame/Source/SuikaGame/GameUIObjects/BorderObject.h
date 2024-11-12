#pragma once
#include "EnginePCH.h"


/// @brief BorderObject 클래스
class BorderObject : public GameObject
{
private:
    std::unique_ptr<FTexture2D> border_texture;

public:
    BorderObject(GameEngine* engine);

protected:
    virtual void Update(float delta_time) override;
    virtual void Render(SDL_Renderer* renderer) const override;
};

#pragma once
#include "EnginePCH.h"


/// @brief Border의 배경을 그리는 GameObject
class BorderBackgroundObject : public GameObject
{
private:
    std::unique_ptr<Texture> border_background_texture;

public:
    BorderBackgroundObject(GameEngine* engine);

    virtual void Render(SDL_Renderer* renderer) override;
};

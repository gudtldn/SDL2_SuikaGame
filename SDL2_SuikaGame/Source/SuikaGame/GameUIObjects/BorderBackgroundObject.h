#pragma once
#include "EnginePCH.h"


/// @brief Border의 배경을 그리는 GameObject
class BorderBackgroundObject : public GameObject
{
private:
    std::unique_ptr<Texture2D> border_background_texture;

public:
    BorderBackgroundObject(GameEngine* engine);

protected:
    virtual void Render(SDL_Renderer* renderer) const override;
};

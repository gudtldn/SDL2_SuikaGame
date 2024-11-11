#pragma once
#include "EngineCore.h"


/// @brief BorderObject
class BorderObject : public GameObject
{
private:
    std::unique_ptr<Texture> border_texture;

public:
    BorderObject(GameEngine* engine);

    virtual void Update(float delta_time) override;
    virtual void Render(SDL_Renderer* renderer) override;
};

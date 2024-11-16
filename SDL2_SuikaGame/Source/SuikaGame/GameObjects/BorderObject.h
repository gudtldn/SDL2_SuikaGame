#pragma once
#include "EnginePCH.h"


/// @brief BorderObject 클래스
class BorderObject : public GameObject
{
private:
    std::unique_ptr<Texture2D> border_texture;
    Vector2D texture_position;

private:
    b2BodyId bodies[3];
    b2ShapeId shapes[3];

public:
    BorderObject(GameEngine* engine);

protected:
    virtual void Update(float delta_time) override;
    virtual void Render(SDL_Renderer* renderer) const override;
    virtual void OnDestroy() override;
};

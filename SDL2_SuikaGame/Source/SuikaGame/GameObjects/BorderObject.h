#pragma once
#include "EnginePCH.h"


/// @brief BorderObject 클래스
class BorderObject : public GameObject
{
private:
    std::unique_ptr<Texture2D> border_texture;
    Vector2D texture_position;

private:
    b2BodyId bodies[2];
    b2ShapeId shapes[2];

public:
    BorderObject(GameEngine* engine);

    /// @brief Border의 위치를 반환합니다.
    Vector2D GetObjectPosition() const { return texture_position; }

protected:
    virtual void BeginPlay() override;
    virtual void Render(SDL_Renderer* renderer) const override;
    virtual void OnDestroy() override;
};

#pragma once
#include "EnginePCH.h"


/// @brief 진화의 고리 표시 객체
class CircleOfEvolutionDisplayObject : public GameObject
{
private:
    /// @brief 진화의 고리 텍스처
    std::unique_ptr<Texture2D> circle_texture;

    /// @brief 진화의 고리 텍스트
    std::unique_ptr<Texture2D> text_texture;

    /// @brief 표시 위치
    Vector2D display_position;

public:
    CircleOfEvolutionDisplayObject(GameEngine* engine);

protected:
    virtual void Render(SDL_Renderer* renderer) const override;
};

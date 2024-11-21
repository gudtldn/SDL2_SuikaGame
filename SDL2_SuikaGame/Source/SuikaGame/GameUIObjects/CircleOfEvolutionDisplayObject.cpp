#include "CircleOfEvolutionDisplayObject.h"


CircleOfEvolutionDisplayObject::CircleOfEvolutionDisplayObject(GameEngine* engine)
    : GameObject(engine)
    , display_position{
        SCREEN_WIDTH * 0.85f,
        SCREEN_HEIGHT * 0.725f
    }
{
    SDL_Texture* raw_circle_texture = IMG_LoadTexture(engine->GetRenderer(), "Contents/Textures/evolution_circle.png");
    THROW_IF_FAILED(
        raw_circle_texture,
        "Failed to load evolution circle texture! SDL Error: {}", SDL_GetError()
    )

    SDL_Texture* raw_text_texture = IMG_LoadTexture(engine->GetRenderer(), "Contents/Textures/evolution_text.png");
    THROW_IF_FAILED(
        raw_text_texture,
        "Failed to load evolution text texture! SDL Error: {}", SDL_GetError()
    )

    circle_texture = std::make_unique<Texture2D>(raw_circle_texture);
    text_texture = std::make_unique<Texture2D>(raw_text_texture);
}

void CircleOfEvolutionDisplayObject::Render(SDL_Renderer* renderer) const
{
    circle_texture->Render(renderer, display_position);
    text_texture->Render(
        renderer,
        {
            display_position.X,
            display_position.Y - 165.0f
        }
    );
}

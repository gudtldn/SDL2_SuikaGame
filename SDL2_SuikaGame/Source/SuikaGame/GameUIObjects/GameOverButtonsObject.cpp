#include "GameOverButtonsObject.h"
#include "SuikaGame/Stages/MenuStage.h"
#include "SuikaGame/Stages/GameStage.h"


GameOverButtonsObject::GameOverButtonsObject(GameEngine* engine)
    : GameObject(engine)
    , restart_button_position({
        250.0f,
        SCREEN_HEIGHT - 75.0f
    })
    , title_button_position({
        550.0f,
        SCREEN_HEIGHT - 75.0f
    })
{
    SDL_Texture* raw_restart_texture = IMG_LoadTexture(engine->GetRenderer(), "./Contents/Textures/restart_button.png");
    SDL_Texture* raw_disable_restart_texture = IMG_LoadTexture(engine->GetRenderer(), "./Contents/Textures/restart_button_disable.png");
    THROW_IF_FAILED(
        raw_restart_texture && raw_disable_restart_texture,
        "Failed to load restart button texture! SDL Error: {}", SDL_GetError()
    )

    SDL_Texture* raw_title_texture = IMG_LoadTexture(engine->GetRenderer(), "./Contents/Textures/main_menu_button.png");
    SDL_Texture* raw_disable_title_texture = IMG_LoadTexture(engine->GetRenderer(), "./Contents/Textures/main_menu_button_disable.png");
    THROW_IF_FAILED(
        raw_title_texture && raw_disable_title_texture,
        "Failed to load title button texture! SDL Error: {}", SDL_GetError()
    )

    restart_button = std::make_unique<TextureButtonComponent>(
        std::make_unique<FTexture2D>(raw_restart_texture)
    );
    restart_button->SetDisableTexture(std::make_unique<FTexture2D>(raw_disable_restart_texture));
    restart_button->SetOnHoverClickedCallback([this]
    {
        GetEngine()->SetStage<GameStage>();
    });

    title_button = std::make_unique<TextureButtonComponent>(
        std::make_unique<FTexture2D>(raw_title_texture)
    );
    title_button->SetDisableTexture(std::make_unique<FTexture2D>(raw_disable_title_texture));
    title_button->SetOnHoverClickedCallback([this]
    {
        GetEngine()->SetStage<MenuStage>();
    });
}

void GameOverButtonsObject::OnEvent(const SDL_Event& event)
{
    const Vector2D restart_button_size = restart_button->GetTexture()->GetSize();
    restart_button->HandleEvents(
        event,
        restart_button_position - restart_button_size / 2
    );

    const Vector2D title_button_size = title_button->GetTexture()->GetSize();
    title_button->HandleEvents(
        event,
        title_button_position - title_button_size / 2
    );
}

void GameOverButtonsObject::Render(SDL_Renderer* renderer) const
{
    restart_button->Render(renderer, restart_button_position);
    title_button->Render(renderer, title_button_position);
}

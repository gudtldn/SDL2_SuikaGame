#include "StartButtonObject.h"


StartButtonObject::StartButtonObject(GameEngine* engine)
    : GameObject(engine)
    , button(nullptr)
{
    // 버튼 텍스처 로드
    SDL_Texture* raw_button_texture = IMG_LoadTexture(engine->GetRenderer(), "Contents/Textures/button.png");
    THROW_IF_FAILED(
        raw_button_texture,
        "Failed to load button texture! SDL Error: %s", SDL_GetError()
    );

    // 버튼 위치 설정
    int button_width, button_height;
    SDL_QueryTexture(raw_button_texture, nullptr, nullptr, &button_width, &button_height);

    button = std::make_unique<Texture>(
        raw_button_texture,
        Vector2D(
            SCREEN_WIDTH / 2 - button_width / 2,
            (SCREEN_HEIGHT / 2 - button_height / 2) * 1.05
        ),
        Vector2D(button_width, button_height)
    );
}

void StartButtonObject::BeginPlay()
{
    button_origin = button->GetPosition();
}

void StartButtonObject::Update(double delta_time)
{
    // 버튼 애니메이션
    Vector2D new_position = button->GetPosition();
    new_position.Y = button_origin.Y + (sin(GetEngine()->GetAccumulatedTime() * BUTTON_OSCILLATION_SPEED) * BUTTON_OSCILLATION_RANGE);
    button->SetPosition(new_position);
}

void StartButtonObject::Render(SDL_Renderer* renderer)
{
    button->Render(renderer);
}

void StartButtonObject::OnEvent(const SDL_Event& event)
{
    if (event.type == SDL_MOUSEBUTTONDOWN)
    {

    }
}

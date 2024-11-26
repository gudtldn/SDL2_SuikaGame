#include "StartButtonObject.h"
#include "SuikaGame/Stages/GameStage.h"


StartButtonObject::StartButtonObject(GameEngine* engine)
    : GameObject(engine)
    , start_button(nullptr)
{
    // 버튼 텍스처 로드
    SDL_Texture* raw_button_texture = IMG_LoadTexture(engine->GetRenderer(), "Contents/Textures/game_start_button.png");
    THROW_IF_FAILED(
        raw_button_texture,
        "Failed to load button texture! SDL Error: {}", SDL_GetError()
    )

    // 버튼 초기화
    start_button = std::make_unique<TextureButtonComponent>(
        std::make_unique<Texture2D>(raw_button_texture)
    );

    start_button->SetOnHoverClickedCallback([this]
    {
        GetEngine()->SetStage<GameStage>();
    });

    // 버튼 초기 위치 설정
    button_origin = Vector2D(
        SCREEN_WIDTH / 2,
        SCREEN_HEIGHT / 2 * 1.05f
    );
}

void StartButtonObject::BeginPlay()
{
    // 버튼의 현재위치 설정
    current_button_position = button_origin;
}

void StartButtonObject::Update(float delta_time)
{
    // 버튼 애니메이션
    current_button_position.Y =
        button_origin.Y + (sin(GetEngine()->GetAccumulatedTime() * BUTTON_OSCILLATION_SPEED) * BUTTON_OSCILLATION_RANGE);
}

void StartButtonObject::Render(SDL_Renderer* renderer) const
{
    start_button->Render(renderer, current_button_position);
}

void StartButtonObject::OnEvent(const SDL_Event& event)
{
    const Vector2D button_size = start_button->GetTexture()->GetSize();
    start_button->HandleEvents(
        event,
        current_button_position - button_size / 2
    );

    // 키보드 및 게임 컨트롤러 버튼 이벤트 처리
    if (
        event.type == SDL_CONTROLLERBUTTONDOWN
        || event.type == SDL_KEYDOWN
    ) {
        if (
            event.cbutton.button == SDL_CONTROLLER_BUTTON_A
            || event.key.keysym.sym == SDLK_SPACE
        ) {
            start_button->SimulateHoverClicked();
        }
    }
}

#include "StartButtonObject.h"
#include "SuikaGame/Stages/GameStage.h"


StartButtonObject::StartButtonObject(GameEngine* engine)
    : GameObject(engine)
    , button_texture(nullptr)
{
    // 버튼 텍스처 로드
    SDL_Texture* raw_button_texture = IMG_LoadTexture(engine->GetRenderer(), "Contents/Textures/game_start_button.png");
    THROW_IF_FAILED(
        raw_button_texture,
        "Failed to load button texture! SDL Error: {}", SDL_GetError()
    )

    // 버튼 텍스처 설절
    button_texture = std::make_unique<FTexture2D>(raw_button_texture);

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
    button_texture->Render(renderer, current_button_position);
}

void StartButtonObject::OnEvent(const SDL_Event& event)
{
    // TODO: 나중에 IButtonObject 인터페이스 만들고
    // TexturedButtonObject도 만들어서 버튼 관련 이벤트 처리를 간결하게 하면 좋을듯

    // 마우스 커서 위치
    const float mouse_x = static_cast<float>(event.motion.x);
    const float mouse_y = static_cast<float>(event.motion.y);

    // 버튼 정보
    const Vector2D button_size = button_texture->GetSize();
    const SDL_FRect button_rect = {
        .x = current_button_position.X - button_size.X / 2,
        .y = current_button_position.Y - button_size.Y / 2,
        .w = button_size.X,
        .h = button_size.Y
    };

    // 마우스 motion 이벤트 처리
    if (event.type == SDL_MOUSEMOTION && event.motion.state == SDL_PRESSED)
    {
        if (is_clicked)
        {
            if (!(mouse_x >= button_rect.x && mouse_x <= button_rect.x + button_rect.w
                  && mouse_y >= button_rect.y && mouse_y <= button_rect.y + button_rect.h))
            {
                is_clicked = false;
            }
        }
    }

    // 마우스 down 이벤트 처리
    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
    {
        is_clicked = mouse_x >= button_rect.x && mouse_x <= button_rect.x + button_rect.w
            && mouse_y >= button_rect.y && mouse_y <= button_rect.y + button_rect.h;
    }

    // 마우스 up 이벤트 처리
    if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT)
    {
        if (is_clicked)
        {
            GetEngine()->SetStage<GameStage>();
            return;
        }
    }


    // 키보드 및 게임 컨트롤러 버튼 이벤트 처리
    if (
        event.type == SDL_CONTROLLERBUTTONDOWN
        || event.type == SDL_KEYDOWN
    ) {
        if (
            event.cbutton.button == SDL_CONTROLLER_BUTTON_A
            || event.key.keysym.sym == SDLK_SPACE
        ) {
            GetEngine()->SetStage<GameStage>();
            return;
        }
    }
}

#include "StartButtonObject.h"
#include "SuikaGame/Stages/GameStage.h"


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

    button = std::make_unique<FTexture2D>(
        raw_button_texture,
        Vector2D(
            static_cast<float>((SCREEN_WIDTH - button_width) / 2),
            static_cast<float>((SCREEN_HEIGHT - button_height) / 2) * 1.05f
        ),
        Vector2D(
            static_cast<float>(button_width),
            static_cast<float>(button_height)
        )
    );
}

void StartButtonObject::BeginPlay()
{
    button_origin = button->GetPosition();
}

void StartButtonObject::Update(float delta_time)
{
    // 버튼 애니메이션
    Vector2D new_position = button->GetPosition();
    new_position.Y = button_origin.Y + (sin(GetEngine()->GetAccumulatedTime() * BUTTON_OSCILLATION_SPEED) * BUTTON_OSCILLATION_RANGE);
    button->SetPosition(new_position);
}

void StartButtonObject::Render(SDL_Renderer* renderer) const
{
    button->Render(renderer);
}

void StartButtonObject::OnEvent(const SDL_Event& event)
{
    // TODO: 나중에 IButtonObject 인터페이스 만들고
    // TexturedButtonObject도 만들어서 버튼 관련 이벤트 처리를 간결하게 하면 좋을듯

    // 마우스 커서 위치
    int mouse_x = event.motion.x;
    int mouse_y = event.motion.y;

    // 버튼 정보
    SDL_FRect button_rect = button->GetRect();

    // 마우스 motion 이벤트 처리
    if (event.type == SDL_MOUSEMOTION)
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
    if (event.type == SDL_MOUSEBUTTONDOWN)
    {
        is_clicked = mouse_x >= button_rect.x && mouse_x <= button_rect.x + button_rect.w
            && mouse_y >= button_rect.y && mouse_y <= button_rect.y + button_rect.h;
    }

    // 마우스 up 이벤트 처리
    if (event.type == SDL_MOUSEBUTTONUP)
    {
        if (is_clicked)
        {
            GetEngine()->SetStage<GameStage>();
            return;
        }
    }


    // 게임 컨트롤러 버튼 이벤트 처리
    if (event.type == SDL_CONTROLLERBUTTONDOWN)
    {
        if (event.cbutton.button == SDL_CONTROLLER_BUTTON_A)
        {
            GetEngine()->SetStage<GameStage>();
            return;
        }
    }
}

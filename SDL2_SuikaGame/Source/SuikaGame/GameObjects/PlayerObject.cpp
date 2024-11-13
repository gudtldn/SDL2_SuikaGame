#include "PlayerObject.h"

// TODO: 가이드라인이 메인이고, Player가 가이드라인을 따라다니는 형태로 구현해야 함
PlayerObject::PlayerObject(GameEngine* engine)
    : GameObject(engine)
    , guide_line(
        Vector2D::Zero,
        Vector2D(
            GUIDE_LINE_WIDTH,
            GUIDE_LINE_HEIGHT
        )
    )
    , player(nullptr)
{
    // z-order 설정
    z_order = -1;

    // 플레이어 텍스처 로드
    SDL_Texture* raw_player_texture = IMG_LoadTexture(engine->GetRenderer(), "Contents/Textures/player.png");
    THROW_IF_FAILED(
        raw_player_texture,
        "Failed to load player texture! SDL Error: {}", SDL_GetError()
    );

    // 플레이어 움직임 제한 설정
    min_player_x = (SCREEN_WIDTH - PLAYER_LINE_WIDTH) / 2.0f;
    max_player_x = min_player_x + PLAYER_LINE_WIDTH - PLAYER_WIDTH;
    player_line_y = SCREEN_HEIGHT / 2.0f - 320.0f;

    // 플레이어 설정
    player = std::make_unique<Texture2D>(
        raw_player_texture,
        Vector2D(
            min_player_x + (PLAYER_LINE_WIDTH - PLAYER_WIDTH) / 2.0f,
            player_line_y - PLAYER_HEIGHT / 2.0f
        ),
        Vector2D(PLAYER_WIDTH, PLAYER_HEIGHT)
    );
}

void PlayerObject::BeginPlay()
{
}

void PlayerObject::Update(float delta_time)
{
    const Uint8* key_states = SDL_GetKeyboardState(nullptr);

    SDL_GameController* gamecontroller = GetEngine()->GetController();
    Sint16 left_stick_x = SDL_GameControllerGetAxis(gamecontroller, SDL_CONTROLLER_AXIS_LEFTX);
    bool dpad_left = SDL_GameControllerGetButton(gamecontroller, SDL_CONTROLLER_BUTTON_DPAD_LEFT);
    bool dpad_right = SDL_GameControllerGetButton(gamecontroller, SDL_CONTROLLER_BUTTON_DPAD_RIGHT);

    // 플레이어 이동
    float new_x = player->GetPosition().X;


    // 조이스틱 입력
    if (
        left_stick_x > JOYSTICK_DEAD_ZONE
        || left_stick_x < -JOYSTICK_DEAD_ZONE
    ) {
        new_x += PLAYER_SPEED * delta_time * (left_stick_x / 32767.0f);
    }

    // 키보드 & D패드 입력
    else
    {
        if (
            key_states[SDL_SCANCODE_LEFT]          // 왼쪽 방향키
            || key_states[SDL_SCANCODE_A]          // A 키
            || dpad_left                           // D-Pad 왼쪽
        ) {
            new_x -= PLAYER_SPEED * delta_time;
        }

        if (
            key_states[SDL_SCANCODE_RIGHT]         // 오른쪽 방향키
            || key_states[SDL_SCANCODE_D]          // D 키
            || dpad_right                          // D-Pad 오른쪽
        ) {
            new_x += PLAYER_SPEED * delta_time;
        }
    }


    // 플레이어 위치 적용
    SetPlayerPosition(new_x);

    float clamped_x = Math::Clamp(new_x, min_player_x, max_player_x);
    guide_line.SetPosition(Vector2D(
        clamped_x + PLAYER_WIDTH / 2.0f - GUIDE_LINE_WIDTH / 2.0f,
        player_line_y
    ));
}

void PlayerObject::Render(SDL_Renderer* renderer) const
{
    guide_line.Render(renderer);
    player->Render(renderer);
}

void PlayerObject::OnEvent(const SDL_Event& event)
{
    if (event.type == SDL_MOUSEMOTION)
    {
        SetPlayerPosition(event.motion.x - PLAYER_WIDTH / 2.0f);
    }
}

inline void PlayerObject::SetPlayerPosition(float x)
{
    x = Math::Clamp(x, min_player_x, max_player_x);
    player->SetPosition(Vector2D(x, player->GetPosition().Y));
}

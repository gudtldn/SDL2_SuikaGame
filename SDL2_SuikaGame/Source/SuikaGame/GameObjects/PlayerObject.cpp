#include "PlayerObject.h"


PlayerObject::PlayerObject(GameEngine* engine)
    : GameObject(engine)
    , player_texture(nullptr)
    , player_guide_line(
        Vector2D::Zero,
        Vector2D(
            GUIDE_LINE_WIDTH,
            GUIDE_LINE_HEIGHT
        )
    )
{
    // z-order 설정
    z_order = -1;

    // 플레이어 텍스처 로드
    SDL_Texture* raw_player_texture = IMG_LoadTexture(engine->GetRenderer(), "Contents/Textures/player.png");
    THROW_IF_FAILED(
        raw_player_texture,
        "Failed to load player texture! SDL Error: {}", SDL_GetError()
    )

    // 플레이어 움직임 제한 설정
    min_border_x = (SCREEN_WIDTH - BORDER_WIDTH) / 2.0f;
    max_border_x = min_border_x + BORDER_WIDTH - GUIDE_LINE_WIDTH;

    // margin 적용
    min_border_x += BORDER_MARGIN;
    max_border_x -= BORDER_MARGIN;

    // player_guide_line의 y 좌표 설정
    player_line_y = SCREEN_HEIGHT / 2.0f - 320.0f;


    // 플레이어 텍스처 생성
    player_texture = std::make_unique<Texture2D>(
        raw_player_texture,
        Vector2D(
            min_border_x + (BORDER_WIDTH - PLAYER_WIDTH) / 2.0f,
            player_line_y - PLAYER_HEIGHT / 2.0f
        ),
        Vector2D(PLAYER_WIDTH, PLAYER_HEIGHT)
    );
}

void PlayerObject::Update(float delta_time)
{
    const Uint8* key_states = SDL_GetKeyboardState(nullptr);

    // 조이스틱 입력
    Sint16 left_stick_x = 0;
    bool dpad_left = false;
    bool dpad_right = false;

    SDL_GameController* game_controller = GetEngine()->GetController();
    if (game_controller != nullptr)
    {
        left_stick_x = SDL_GameControllerGetAxis(game_controller, SDL_CONTROLLER_AXIS_LEFTX);
        dpad_left = SDL_GameControllerGetButton(game_controller, SDL_CONTROLLER_BUTTON_DPAD_LEFT);
        dpad_right = SDL_GameControllerGetButton(game_controller, SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
    }

    // 플레이어 이동
    float new_x = player_guide_line.GetPosition().X;


    // 조이스틱 입력
    if (
        left_stick_x > JOYSTICK_DEAD_ZONE
        || left_stick_x < -JOYSTICK_DEAD_ZONE
    ) {
        new_x += PLAYER_SPEED * delta_time * (static_cast<float>(left_stick_x) / 32767.0f);
    }

    // 키보드 & D패드 입력
    else
    {
        if (
            key_states[SDL_SCANCODE_LEFT]        // 왼쪽 방향키
            || key_states[SDL_SCANCODE_A]        // A 키
            || dpad_left                         // D-Pad 왼쪽
        ) {
            new_x -= PLAYER_SPEED * delta_time;
        }

        if (
            key_states[SDL_SCANCODE_RIGHT]       // 오른쪽 방향키
            || key_states[SDL_SCANCODE_D]        // D 키
            || dpad_right                        // D-Pad 오른쪽
        ) {
            new_x += PLAYER_SPEED * delta_time;
        }
    }


    // 플레이어 위치 적용
    SetPlayerPosition(new_x);

    // 플레이어 텍스처 위치 설정
    player_texture->SetPosition(Vector2D(
        player_guide_line.GetPosition().X - (PLAYER_WIDTH * 0.15f),
        player_line_y - PLAYER_HEIGHT / 2.0f
    ));
}

void PlayerObject::Render(SDL_Renderer* renderer) const
{
    player_guide_line.Render(renderer);
    player_texture->Render(renderer);
}

void PlayerObject::OnEvent(const SDL_Event& event)
{
    if (event.type == SDL_MOUSEMOTION)
    {
        SetPlayerPosition(
            static_cast<float>(event.motion.x)
        );
    }

    if (event.type == SDL_MOUSEBUTTONDOWN)
    {
        // TODO: 과일 생성
    }
}

inline void PlayerObject::SetPlayerPosition(float new_x)
{
    const float clamped_x = Math::Clamp(new_x, min_border_x, max_border_x);
    player_guide_line.SetPosition(Vector2D(
        clamped_x,
        player_line_y
    ));
}

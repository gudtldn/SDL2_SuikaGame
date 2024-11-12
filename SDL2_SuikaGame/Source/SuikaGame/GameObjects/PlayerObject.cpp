#include "PlayerObject.h"


PlayerObject::PlayerObject(GameEngine* engine)
    : GameObject(engine)
    , guide_line(
        Vector2D::Zero,
        Vector2D(
            GUIDE_LINE_WIDTH,
            GUIDE_LINE_HEIGHT
        )
    )
{
    // z-order 설정
    z_order = -1;

    // 플레이어 움직임 제한 설정
    min_player_x = SCREEN_WIDTH / 2.0 - PLAYER_LINE_WIDTH / 2.0;
    max_player_x = min_player_x + PLAYER_LINE_WIDTH - PLAYER_SIZE;
    player_line_y = SCREEN_HEIGHT / 2.0 - 280;

    // 플레이어 설정
    player.SetPosition(Vector2D(
        min_player_x + (PLAYER_LINE_WIDTH - PLAYER_SIZE) / 2.0,
        player_line_y - PLAYER_SIZE / 2.0
    ));
    player.SetSize(Vector2D(PLAYER_SIZE, PLAYER_SIZE));
    player.SetColor(255, 0, 0, 255);
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
    double new_x = player.GetPosition().X;


    // 조이스틱 입력
    if (
        left_stick_x > JOYSTICK_DEAD_ZONE
        || left_stick_x < -JOYSTICK_DEAD_ZONE
    ) {
        new_x += PLAYER_SPEED * delta_time * (left_stick_x / 32767.0);
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
    guide_line.SetPosition(Vector2D(
        new_x + PLAYER_SIZE / 2.0 - GUIDE_LINE_WIDTH / 2.0,
        player_line_y
    ));
}

void PlayerObject::Render(SDL_Renderer* renderer) const
{
    guide_line.Render(renderer);
    player.Render(renderer);
}

void PlayerObject::OnEvent(const SDL_Event& event)
{
    if (event.type == SDL_MOUSEMOTION)
    {
        SetPlayerPosition(event.motion.x - PLAYER_SIZE / 2.0);
    }
}

inline void PlayerObject::SetPlayerPosition(double x)
{
    x = Math::Clamp(x, min_player_x, max_player_x);
    player.SetPosition(Vector2D(x, player.GetPosition().Y));
}

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

    // 가이드 선 설정
}

void PlayerObject::BeginPlay()
{
}

void PlayerObject::Update(float delta_time)
{
    const Uint8* key_states = SDL_GetKeyboardState(nullptr);

    double new_x = player.GetPosition().X;

    if (key_states[SDL_SCANCODE_LEFT])
    {
        new_x -= PLAYER_SPEED * delta_time;
    }
    else if (key_states[SDL_SCANCODE_RIGHT])
    {
        new_x += PLAYER_SPEED * delta_time;
    }

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

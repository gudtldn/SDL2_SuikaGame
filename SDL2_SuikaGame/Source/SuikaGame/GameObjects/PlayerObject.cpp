#include "PlayerObject.h"
#include "FruitObject.h"


PlayerObject::PlayerObject(GameEngine* engine)
    : GameObject(engine)
    , player_texture(nullptr)
    , player_guide_line(
        Vector2D(
            GUIDE_LINE_WIDTH,
            GUIDE_LINE_HEIGHT
        )
    )
    , current_fruit(nullptr)
    , next_fruit(nullptr)
    , next_fruit_ready(false)
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
    player_position.X = SCREEN_WIDTH / 2.0f;
    player_position.Y = SCREEN_HEIGHT / 2.0f - 320.0f;


    // 플레이어 텍스처 생성
    player_texture = std::make_unique<Texture2D>(
        raw_player_texture,
        Vector2D(PLAYER_WIDTH, PLAYER_HEIGHT)
    );
}

void PlayerObject::BeginPlay()
{
    FruitObject* fruit = GetCurrentStage()->GetObjectManager().CreateGameObject<FruitObject>();
    fruit->InitRandomFruit();
    next_fruit = fruit;

    // NextFruitDisplayObject::BeginPlay에 델리게이트 함수가 바인딩되어 있음
    next_fruit_delegate.Execute(next_fruit);
    next_fruit_ready = true;

    SetNextFruit();
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
    float new_x = player_position.X;

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

    if (current_fruit != nullptr && !current_fruit->GetFruitActive())
    {
        current_fruit->SetFruitPosition(player_position);
    }
}

void PlayerObject::Render(SDL_Renderer* renderer) const
{
    if (next_fruit_ready)
    {
        player_guide_line.Render(renderer, player_position);
    }

    player_texture->Render(
        renderer,
        Vector2D(
            player_position.X - (PLAYER_WIDTH * 0.15f),
            player_position.Y - PLAYER_HEIGHT / 2.0f
        )
    );
}

void PlayerObject::OnEvent(const SDL_Event& event)
{
    if (event.type == SDL_MOUSEMOTION)
    {
        SetPlayerPosition(
            static_cast<float>(event.motion.x)
        );
    }

    if (
        event.type == SDL_MOUSEBUTTONDOWN                       // 마우스 버튼을 누를 때
        || event.type == SDL_KEYDOWN                            // 키보드 키를 누를 때
        || event.type == SDL_CONTROLLERBUTTONDOWN               // 컨트롤러 버튼을 누를 때
    ) {
        // 다음 과일이 준비되지 않았다면 리턴
        if (!next_fruit_ready) return;

        if (
            event.button.button == SDL_BUTTON_LEFT              // 마우스 왼쪽 버튼
            || event.key.keysym.sym == SDLK_SPACE               // 키보드 스페이스바
            || event.key.keysym.sym == SDLK_DOWN                // 키보드 방향키 아래
            || event.cbutton.button == SDL_CONTROLLER_BUTTON_A  // 컨트롤러 A 버튼
        ) {
            current_fruit->SetFruitActive(true);
            next_fruit_ready = false;
        }
    }
}

void PlayerObject::SetPlayerPosition(float new_x)
{
    player_position.X = Math::Clamp(new_x, min_border_x, max_border_x);
}

void PlayerObject::SetNextFruit()
{
    current_fruit = next_fruit;
    current_fruit->SetFruitPosition(player_position);
    current_fruit->OnLandedBottomCollision.BindFunction([this]()
    {
        SetNextFruit();
    });

    FruitObject* fruit = GetCurrentStage()->GetObjectManager().CreateGameObject<FruitObject>();
    fruit->InitRandomFruit();
    next_fruit = fruit;

    // NextFruitDisplayObject::BeginPlay에 델리게이트 함수가 바인딩되어 있음
    next_fruit_delegate.Execute(next_fruit);
    next_fruit_ready = true;
}

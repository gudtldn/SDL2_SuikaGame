#include "App.h"
#include "Components/Stage.h"
#include "Components/GameObject.h"

#include <vector>
#include <stdexcept>
#include <SDL.h>


App::App(
    const char* title_name,
    int screen_x,
    int screen_y,
    int screen_width,
    int screen_height
)
    : is_running(false)
{
    // SDL 미 초기화 시 예외 처리
    if (SDL_WasInit(SDL_INIT_VIDEO) == 0)
    {
        throw std::runtime_error("SDL is not initialized.");
    }

    // SDL 화면 생성
    window = SDL_CreateWindow(
        title_name,
        screen_x, screen_y,
        screen_width, screen_height,
        SDL_WINDOW_SHOWN
    );
    if (window == nullptr)
    {
        throw std::runtime_error("Failed to create window.");
    }

    // SDL 렌더러 생성
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr)
    {
        throw std::runtime_error("Failed to create renderer.");
    }
}

App::~App()
{
    // SDL 렌더러 해제
    if (renderer != nullptr)
    {
        SDL_DestroyRenderer(renderer);
    }

    // SDL 화면 해제
    if (window != nullptr)
    {
        SDL_DestroyWindow(window);
    }
}

void App::Run()
{
    is_running = true;

    while (is_running)
    {
        // 이벤트 처리
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                is_running = false;
                break;
            }
        }

        // 업데이트
        Update(0.0f); // TODO: delta time 구현

        // 화면 지우기
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // 렌더링
        Render();

        // 화면 업데이트
        SDL_RenderPresent(renderer);
    }
}

void App::Update(double delta_time)
{
    // 현재 스테이지 업데이트
    if (current_stage != nullptr)
    {
        current_stage->Update(delta_time);
    }

    // 게임 오브젝트 업데이트
    for (auto& game_object : game_objects)
    {
        game_object->Update(delta_time);
    }
}

void App::Render()
{
    std::vector<std::shared_ptr<GameObject>> render_objects;

    // 게임 오브젝트 렌더링
    for (auto& game_object : game_objects)
    {
        render_objects.push_back(game_object);
    }

    // 현재 스테이지 렌더링
    if (current_stage != nullptr)
    {
        for (auto& game_object : current_stage->GetGameObjects())
        {
            render_objects.push_back(game_object);
        }
    }
}

template <typename S>
    requires std::derived_from<S, Stage>
void App::SetStage()
{
    current_stage = std::make_unique<S>();
}

#include "FruitResourceObject.h"
#include <ranges>

// TODO: 나중에 스프라이트 시트로 변경
// 과일 이미지 Path
static constexpr std::array fruits_png_path = {
    "Contents/Textures/fruits/fruit_0.png",  // 체리
    "Contents/Textures/fruits/fruit_1.png",  // 딸기
    "Contents/Textures/fruits/fruit_2.png",  // 포도
    "Contents/Textures/fruits/fruit_3.png",  // 오렌지
    "Contents/Textures/fruits/fruit_4.png",  // 감
    "Contents/Textures/fruits/fruit_5.png",  // 사과
    "Contents/Textures/fruits/fruit_6.png",  // 자몽
    "Contents/Textures/fruits/fruit_7.png",  // 복숭아
    "Contents/Textures/fruits/fruit_8.png",  // 파인애플
    "Contents/Textures/fruits/fruit_9.png",  // 멜론
    "Contents/Textures/fruits/fruit_10.png", // 수박
};

// 과일 이미지 스케일
static constexpr std::array fruits_scale = {
    0.175f,  // 체리
    0.2f,    // 딸기
    0.275f,  // 포도
    0.3f,    // 오렌지
    0.375f,  // 감
    0.425f,  // 사과
    0.55f,   // 자몽
    0.65f,   // 복숭아
    0.8f,    // 파인애플
    0.875f,  // 멜론
    1.0f,    // 수박
};

FruitResourceObject::FruitResourceObject()
    : fruits_offset_position {
        Vector2D(-1.0f, 4.5f),  // 체리
        Vector2D(-1.0f, 0.0f),  // 딸기
        Vector2D(-1.0f, 0.0f),  // 포도
        Vector2D(-1.0f, 1.0f),  // 오렌지
        Vector2D(-1.0f, 4.0f),  // 감
        Vector2D(-1.0f, 1.0f),  // 사과
        Vector2D(-1.0f, 1.0f),  // 자몽
        Vector2D(-1.0f, -2.0f), // 복숭아
        Vector2D(-1.0f, 12.0f), // 파인애플
        Vector2D(0.0f, 0.0f),   // 멜론
        Vector2D(0.0f, 0.0f),   // 수박
    }
    , fruits_offset_size {
        -5.0f,  // 체리
        0.0f,   // 딸기
        0.0f,   // 포도
        -4.0f,  // 오렌지
        -5.0f,  // 감
        -2.0f,  // 사과
        -4.0f,  // 자몽
        -1.0f,  // 복숭아
        -16.0f, // 파인애플
        -1.0f,  // 멜론
        -1.0f,  // 수박
    }
    , fruit_merge_sound(nullptr, Mix_FreeChunk)
{
}

void FruitResourceObject::Load()
{
    // pop 사운드 로드
    Mix_Chunk* raw_fruit_merge_sound = Mix_LoadWAV("Contents/Sounds/pop.mp3");
    THROW_IF_FAILED(
        raw_fruit_merge_sound,
        "Failed to load fruit merge sound! SDL_mixer Error: {}", Mix_GetError()
    )
    fruit_merge_sound.reset(raw_fruit_merge_sound);

    // 과일 이미지 로드
    for (const auto [idx, png] : fruits_png_path | std::ranges::views::enumerate)
    {
        SDL_Texture* raw_fruit_texture = IMG_LoadTexture(engine->GetRenderer(), png);
        THROW_IF_FAILED(
            raw_fruit_texture,
            "Failed to load fruit texture! SDL Error: {}", SDL_GetError()
        )

        int w, h;
        SDL_QueryTexture(raw_fruit_texture, nullptr, nullptr, &w, &h);

        fruit_textures[idx] = std::make_unique<Texture2D>(
            raw_fruit_texture,
            Vector2D(
                static_cast<float>(w) * fruits_scale.at(idx),
                static_cast<float>(h) * fruits_scale.at(idx)
            )
        );
    }
}

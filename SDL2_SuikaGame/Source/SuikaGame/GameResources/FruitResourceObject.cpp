#include "FruitResourceObject.h"


FruitResourceObject::FruitResourceObject(GameEngine* engine)
    : GameObject(engine)
{
    // TODO: 나중에 스프라이트 시트로 변경
    const char* fruits_png[] = {
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

    constexpr float fruit_scales[] = {
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

    for (size_t i = 0; i < fruit_textures.max_size(); ++i)
    {
        SDL_Texture* raw_fruit_texture = IMG_LoadTexture(engine->GetRenderer(), fruits_png[i]);
        THROW_IF_FAILED(
            raw_fruit_texture,
            "Failed to load fruit texture! SDL Error: {}", SDL_GetError()
        )

        int w, h;
        SDL_QueryTexture(raw_fruit_texture, nullptr, nullptr, &w, &h);

        fruit_textures[i] = std::make_unique<Texture2D>(
            raw_fruit_texture,
            Vector2D(
                static_cast<float>(w) * fruit_scales[i],
                static_cast<float>(h) * fruit_scales[i]
            )
        );
    }
}

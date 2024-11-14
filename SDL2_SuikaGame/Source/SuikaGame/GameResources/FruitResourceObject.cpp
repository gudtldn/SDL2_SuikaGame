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

    for (size_t i = 0; i < fruit_textures.max_size(); ++i)
    {
        SDL_Texture* raw_fruit_texture = IMG_LoadTexture(engine->GetRenderer(), fruits_png[i]);
        THROW_IF_FAILED(
            raw_fruit_texture,
            "Failed to load fruit texture! SDL Error: {}", SDL_GetError()
        )

        fruit_textures[i] = std::make_unique<Texture2D>(raw_fruit_texture, Vector2D::Zero);
    }
}

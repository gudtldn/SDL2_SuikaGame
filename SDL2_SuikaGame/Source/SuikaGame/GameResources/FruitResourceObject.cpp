#include "FruitResourceObject.h"

#include <__msvc_filebuf.hpp>


FruitResourceObject::FruitResourceObject(GameEngine* engine)
    : GameObject(engine)
{
    // TODO: 나중에 스프라이트 시트로 변경
    const char* fruits_png[] = {
        "Contents/Textures/fruits/fruit_1.png",
        "Contents/Textures/fruits/fruit_2.png",
        "Contents/Textures/fruits/fruit_3.png",
        "Contents/Textures/fruits/fruit_4.png",
        "Contents/Textures/fruits/fruit_5.png",
        "Contents/Textures/fruits/fruit_6.png",
        "Contents/Textures/fruits/fruit_7.png",
        "Contents/Textures/fruits/fruit_8.png",
        "Contents/Textures/fruits/fruit_9.png",
        "Contents/Textures/fruits/fruit_10.png",
        "Contents/Textures/fruits/fruit_11.png",
    };

    for (size_t i = 0; i < fruit_textures.max_size(); ++i)
    {
        SDL_Texture* raw_fruit_texture = IMG_LoadTexture(engine->GetRenderer(), fruits_png[i]);
        THROW_IF_FAILED(
            raw_fruit_texture,
            "Failed to load border background texture! SDL Error: {}", SDL_GetError()
        )

        fruit_textures[i] = std::make_unique<Texture2D>(raw_fruit_texture, Vector2D::Zero);
    }
}

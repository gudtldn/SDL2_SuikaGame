#pragma once
#include "EnginePCH.h"
#include <array>


// TODO: 나중에 ResourceManager만들어서 관리
class FruitResourceObject : public GameObject
{
public:
    static constexpr size_t FRUIT_COUNT = 11;

private:
    std::array<std::unique_ptr<Texture2D>, FRUIT_COUNT> fruit_textures;

    /// @brief 물리엔진에 사용될 과일의 오프셋 위치
    std::array<Vector2D, FRUIT_COUNT> fruits_offset_position;

    /// @brief 물리엔진에 사용될 과일의 오프셋 사이즈
    std::array<float, FRUIT_COUNT> fruits_offset_size;

    /// 과일 합치는 사운드
    std::unique_ptr<Mix_Chunk, decltype(&Mix_FreeChunk)> fruit_merge_sound;

public:
    FruitResourceObject(GameEngine* engine);


    /****** Getters ******/

    void GetFruit(size_t idx, Texture2D*& texture, Vector2D& offset_pos, float& offset_size) const
    {
        texture = fruit_textures.at(idx).get();
        offset_pos = fruits_offset_position.at(idx);
        offset_size = fruits_offset_size.at(idx);
    }

    Mix_Chunk* GetFruitMergeSound() const
    {
        return fruit_merge_sound.get();
    }
};

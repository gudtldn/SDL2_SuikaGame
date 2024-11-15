#pragma once
#include "EnginePCH.h"
#include <array>


// TODO: 나중에 ResourceManager만들어서 관리
class FruitResourceObject : public GameObject
{
private:
    static constexpr size_t FRUIT_COUNT = 11;

    std::array<std::unique_ptr<Texture2D>, FRUIT_COUNT> fruit_textures;
    std::array<Vector2D, FRUIT_COUNT> fruits_offset_position;
    std::array<float, FRUIT_COUNT> fruits_offset_size;

public:
    FruitResourceObject(GameEngine* engine);


    /****** Getters ******/

    /// @brief 과일 텍스쳐를 가져옵니다.
    /// @param idx 과일 인덱스 (0 ~ 10)
    /// @return 과일 텍스쳐
    /// @throw std::out_of_range idx가 0보다 작거나 10보다 큰 경우
    const Texture2D* GetFruitTexture(size_t idx) const
    {
        return fruit_textures.at(idx).get();
    }

    /// @brief 랜덤한 과일 텍스쳐를 가져옵니다.
    /// @param min_idx 최소 과일 인덱스 (0 ~ max)
    /// @param max_idx 최대 과일 인덱스 (min ~ 10)
    /// @return 과일 텍스쳐
    /// @throw std::out_of_range min_idx가 0보다 작거나 10보다 큰 경우
    /// @throw std::out_of_range max_idx가 min_idx보다 작거나 10보다 큰 경우
    const Texture2D* GetRandomFruitTexture(size_t min_idx, size_t max_idx) const
    {
        return GetFruitTexture(Math::RandRange(
            static_cast<int>(min_idx),
            static_cast<int>(max_idx)
        ));
    }

    /// @brief 과일 텍스쳐의 오프셋을 가져옵니다.
    /// @param idx 과일 인덱스 (0 ~ 10)
    /// @return 과일 텍스쳐의 오프셋
    /// @throw std::out_of_range idx가 0보다 작거나 10보다 큰 경우
    Vector2D GetFruitOffsetPosition(size_t idx) const
    {
        return fruits_offset_position.at(idx);
    }

    /// @brief 과일 텍스쳐의 오프셋을 가져옵니다.
    /// @param idx 과일 인덱스 (0 ~ 10)
    /// @return 과일 텍스쳐의 오프셋
    /// @throw std::out_of_range idx가 0보다 작거나 10보다 큰 경우
    float GetFruitOffsetSize(size_t idx) const
    {
        return fruits_offset_size.at(idx);
    }

};

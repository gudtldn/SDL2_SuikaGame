﻿#pragma once
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

    void GetFruit(size_t idx, Texture2D*& texture, Vector2D& offset_pos, float& offset_size) const
    {
        texture = fruit_textures.at(idx).get();
        offset_pos = fruits_offset_position.at(idx);
        offset_size = fruits_offset_size.at(idx);
    }
};

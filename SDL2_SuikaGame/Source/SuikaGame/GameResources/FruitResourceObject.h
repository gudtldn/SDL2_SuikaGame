#pragma once
#include <EnginePCH.h>
#include <array>


// TODO: 나중에 ResourceManager만들어서 관리
class FruitResourceObject : public GameObject
{
private:
    std::array<std::unique_ptr<Texture2D>, 11> fruit_textures;

public:
    FruitResourceObject(GameEngine* engine);

    /****** Getters ******/

    /// @brief 과일 텍스쳐를 가져옵니다.
    /// @param idx 과일 인덱스 (0 ~ 10)
    /// @return 과일 텍스쳐
    /// @throw std::out_of_range idx가 0보다 작거나 10보다 큰 경우
    const Texture2D* GetFruitTexture(size_t idx) const { return fruit_textures[idx].get(); }
    const Texture2D* GetRandomFruitTexture() const { return GetFruitTexture(Math::RandRange(0, 10)); }
};

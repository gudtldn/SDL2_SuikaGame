#pragma once
#include "EnginePCH.h"


/// @brief 게임오버전 화면을 임시로 저장하는 리소스
class TempScreenCaptureResource : public GameResource
{
    /// @brief 스샷을 임시저장할 객체
    std::unique_ptr<Texture2D> temp_texture_capture;

public:
    virtual void Load() override;

    /// @brief 텍스처를 반환합니다.
    /// @return 텍스처
    std::unique_ptr<Texture2D> MoveTexture();

    /// @brief 텍스처를 설정합니다.
    /// @param in_texture 설정할 텍스처
    void SetTexture(std::unique_ptr<Texture2D> in_texture);
};

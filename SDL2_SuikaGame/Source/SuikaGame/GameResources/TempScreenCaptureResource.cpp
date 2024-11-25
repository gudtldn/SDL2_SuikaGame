#include "TempScreenCaptureResource.h"


std::unique_ptr<Texture2D> TempScreenCaptureResource::MoveTexture()
{
    return std::move(temp_texture_capture);
}

void TempScreenCaptureResource::SetTexture(std::unique_ptr<Texture2D> in_texture)
{
    temp_texture_capture = std::move(in_texture);
}

void TempScreenCaptureResource::Load()
{
}

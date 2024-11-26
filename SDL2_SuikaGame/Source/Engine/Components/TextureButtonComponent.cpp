#include "TextureButtonComponent.h"
#include "Engine/Components/FTexture2D.h"


TextureButtonComponent::TextureButtonComponent(FTexture2D* texture)
    : texture(texture)
    , disable_texture(nullptr)
{
}

TextureButtonComponent::TextureButtonComponent(std::unique_ptr<FTexture2D> texture)
    : texture(std::move(texture))
    , disable_texture(nullptr)
{
}

void TextureButtonComponent::HandleEvents(const SDL_Event& event, const Vector2D& position)
{
    const float mx = static_cast<float>(event.motion.x);
    const float my = static_cast<float>(event.motion.y);
    const Vector2D texture_size = texture->GetSize();

    // 마우스가 버튼 안에 있는지
    const bool inside = (
        mx >= position.X && mx <= position.X + texture_size.X
        && my >= position.Y && my <= position.Y + texture_size.Y
    );

    if (event.type == SDL_MOUSEMOTION)
    {
        if (inside)
        {
            if (!is_hovered && on_hover_callback)
            {
                on_hover_callback();
            }
            is_hovered = true;
        }
        else
        {
            if (is_hovered && on_unhover_callback)
            {
                on_unhover_callback();
            }
            is_hovered = false;
        }
    }

    if (event.type == SDL_MOUSEBUTTONDOWN)
    {
        if (inside && event.button.button == SDL_BUTTON_LEFT)
        {
            is_pressed = true;
            if (on_click_callback)
            {
                on_click_callback();
            }
        }
    }

    if (event.type == SDL_MOUSEBUTTONUP)
    {
        if (
            is_hovered && is_pressed
            && event.button.button == SDL_BUTTON_LEFT
        ) {
            if (on_hover_clicked_callback)
            {
                on_hover_clicked_callback();
            }
        }

        if (is_pressed && event.button.button == SDL_BUTTON_LEFT)
        {
            is_pressed = false;
            if (on_release_callback)
            {
                on_release_callback();
            }
        }
    }
}

void TextureButtonComponent::Render(
    SDL_Renderer* renderer, const Vector2D& position, RenderAnchor anchor, float angle
) const {
    if (disable_texture && !is_hovered)
    {
        disable_texture->Render(renderer, position, anchor, angle);
    }
    else
    {
        texture->Render(renderer, position, anchor, angle);
    }
}

void TextureButtonComponent::SimulateHover()
{
    if (on_hover_callback)
    {
        on_hover_callback();
    }
    is_hovered = true;
}

void TextureButtonComponent::SimulateUnhover()
{
    if (on_unhover_callback)
    {
        on_unhover_callback();
    }
    is_hovered = false;
}

void TextureButtonComponent::SimulateClick()
{
    if (on_click_callback)
    {
        on_click_callback();
    }
    is_pressed = true;
}

void TextureButtonComponent::SimulateRelease()
{
    if (on_release_callback)
    {
        on_release_callback();
    }
    is_pressed = false;
}

void TextureButtonComponent::SimulateClickAndRelease()
{
    SimulateClick();
    SimulateRelease();
}

void TextureButtonComponent::SimulateHoverClicked() const
{
    if (on_hover_clicked_callback)
    {
        on_hover_clicked_callback();
    }
}

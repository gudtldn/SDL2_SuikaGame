#include "Button.h"
#include "Window.h"

Button CreateButton(SDL_FRect rect, SDL_Texture* texture)
{
    return (Button) {
        .rect = rect,
        .texture = texture,
        .is_hovered = false,
        .is_clicked = false
    };
}

void UpdateHandleButton(View* view, Button* button, void (*callback)(View*))
{
    int mouse_x, mouse_y;
    Uint32 state = SDL_GetMouseState(&mouse_x, &mouse_y);

    button->is_hovered = mouse_x >= button->rect.x && mouse_x <= button->rect.x + button->rect.w &&
                         mouse_y >= button->rect.y && mouse_y <= button->rect.y + button->rect.h;

    if (button->is_hovered && state & SDL_BUTTON(SDL_BUTTON_LEFT))
    {
        button->is_clicked = true;
        callback(view);
    }
    else
    {
        button->is_clicked = false;
    }
}

void RenderButton(SDL_Renderer* renderer, Button* button)
{
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderCopyF(renderer, button->texture, NULL, &button->rect);
}

void DestroyButton(Button* button)
{
    SDL_DestroyTexture(button->texture);
    button->texture = NULL;
}

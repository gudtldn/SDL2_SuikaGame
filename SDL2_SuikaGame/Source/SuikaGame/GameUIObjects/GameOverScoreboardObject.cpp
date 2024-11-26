#include "GameOverScoreboardObject.h"
#include "SuikaGame/GameResources/ScoreResource.h"


GameOverScoreboardObject::GameOverScoreboardObject(GameEngine* engine)
    : GameObject(engine)
{
    // ReSharper disable once StringLiteralTypo
    score_text = std::make_unique<TextRender>("./Contents/Fonts/Jalnan2TTF.ttf", 48);
}

void GameOverScoreboardObject::BeginPlay()
{
    const ScoreResource* score_resource =
        GetEngine()->GetResourceManager().GetResource<ScoreResource>();

    score_text->SetText(std::to_string(score_resource->GetScore()));
}

void GameOverScoreboardObject::Render(SDL_Renderer* renderer) const
{
    score_text->Render(renderer, {
        SCREEN_WIDTH / 2 + 385.0f,
        SCREEN_HEIGHT / 2 - 150.0f,
    });
}

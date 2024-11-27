// ReSharper disable StringLiteralTypo
#include "ScoreboardObject.h"
#include "SuikaGame/GameResources/ScoreResource.h"


ScoreboardObject::ScoreboardObject(GameEngine* engine)
    : GameObject(engine)
    , display_position{
        SCREEN_WIDTH * 0.15f,  // 화면 너비의 15%
        SCREEN_HEIGHT * 0.3f   // 화면 높이의 30%
    }
{
    // 스코어보드 배경 텍스처 로드
    SDL_Texture* raw_bubble_texture = IMG_LoadTexture(engine->GetRenderer(), "Contents/Textures/bubble.png");
    THROW_IF_FAILED(
        raw_bubble_texture,
        "Failed to load bubble texture! SDL Error: {}", SDL_GetError()
    )

    // 스코어 텍스트 이미지 로드
    SDL_Texture* raw_score_label_texture = IMG_LoadTexture(engine->GetRenderer(), "Contents/Textures/score_text.png");
    THROW_IF_FAILED(
        raw_score_label_texture,
        "Failed to load score label texture! SDL Error: {}", SDL_GetError()
    )

    // 텍스처 객체 생성
    bubble_texture = std::make_unique<Texture2D>(raw_bubble_texture);
    score_label_texture = std::make_unique<Texture2D>(raw_score_label_texture);

    // 현재 점수 초기화
    score_text = std::make_unique<TextRender>("./Contents/Fonts/Hakgyoansim Dunggeunmiso TTF R.ttf", 48);

    // 최고 점수 레이블 초기화
    high_score_label = std::make_unique<TextRender>("./Contents/Fonts/Jalnan2TTF.ttf", 18);
    high_score_label->SetText("BEST SCORE");
    high_score_label->SetColor({ 0xFF, 0xD3, 0x79, 0xFF });  // 밝은 노란색

    // 최고 점수 초기화
    high_score_text = std::make_unique<TextRender>("./Contents/Fonts/Jalnan2TTF.ttf", 26);
    high_score_text->SetColor({ 0xFF, 0xF3, 0x9B, 0xFF });   // 밝은 황금색


    // 점수 리소스 가져오기
    ScoreResource* score_resource = GetEngine()->GetResourceManager().GetResource<ScoreResource>();

    // 초기 점수 설정
    score_resource->ResetScore();
    score_text->SetText("0");
    score_resource->OnUpdateScoreDelegate.BindFunction([this, score_resource]
    {
        score_text->SetText(std::to_string(score_resource->GetScore()));
    });

    // 최고 점수 초기 설정
    high_score_text->SetText(std::to_string(score_resource->GetHighScore()));
    score_resource->OnUpdateHighScoreDelegate.BindFunction([this, score_resource]
    {
        high_score_text->SetText(std::to_string(score_resource->GetHighScore()));
    });

    origin = display_position;
    random_offset = Math::RandRange(-1.0f, 1.0f);
}

void ScoreboardObject::Update(float delta_time)
{
    display_position.Y =
        origin.Y + (Math::Sin((GetEngine()->GetAccumulatedTime() + random_offset) * 2.0f) * 8.0f);
}

void ScoreboardObject::Render(SDL_Renderer* renderer) const
{
    bubble_texture->Render(renderer, display_position);

    // 현재 점수 렌더링
    score_label_texture->Render(
        renderer,
        {
            display_position.X,
            display_position.Y - 122.5f
        }
    );
    score_text->Render(
        renderer,
        {
            display_position.X,
            display_position.Y - 40.0f
        }
    );

    // 최고 점수 렌더링
    high_score_label->Render(
        renderer,
        {
            display_position.X,
            display_position.Y + 10.0f
        }
    );
    high_score_text->Render(
        renderer,
        {
        display_position.X,
        display_position.Y + 40.0f
        }
    );
}

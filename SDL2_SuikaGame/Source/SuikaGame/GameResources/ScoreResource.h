#pragma once
#include "EnginePCH.h"
#include <filesystem>

// delegate declaration
DECLARE_DELEGATE(FUpdateScoreDelegate);
DECLARE_DELEGATE(FUpdateHighScoreDelegate);


/// @brief 점수와 관련된 리소스
class ScoreResource : public GameResource
{
    /// @brief 현재 게임의 점수
    int score = 0;

    /// @brief 최고점수
    int high_score = 0;

    /// @brief 세이브 파일 경로
    std::filesystem::path save_file_path;

public:
    /// @brief 점수가 업데이트될 때 호출되는 델리게이트
    FUpdateScoreDelegate OnUpdateScoreDelegate;

    /// @brief 최고점수가 업데이트 될 때 호출되는 델리게이트
    FUpdateHighScoreDelegate OnUpdateHighScoreDelegate;

public:
    ScoreResource();
    virtual void Load() override;

    /// @brief 게임의 점수를 가져옵니다.
    [[nodiscard]] int GetScore() const { return score; }

    /// @brief 점수를 추가합니다.
    void AddScore(int value)
    {
        score += value;
        OnUpdateScoreDelegate.Execute();
    }

    /// @brief 점수를 초기화 합니다.
    void ResetScore() { score = 0; }

    /// @brief 최고점수를 가져옵니다.
    [[nodiscard]] int GetHighScore() const { return high_score; }

    /// @brief 최고점수를 설정합니다.
    void SetHighScore(int value)
    {
        high_score = value;
        OnUpdateHighScoreDelegate.Execute();
    }

    /// @brief 세이브 파일로부터 불러옵니다.
    void LoadFromFile();

    /// @brief 현재 상태를 세이브 파일로 저장합니다.
    void SaveToFile();
};

#include "GameOverStage.h"
#include "SuikaGame/GameUIObjects/GameOverBackgroundObject.h"
#include "SuikaGame/GameUIObjects/GameOverScreenCaptureDisplayObject.h"
#include "SuikaGame/GameUIObjects/GameOverButtonsObject.h"


void GameOverStage::InitializeStage()
{
    // 게임오버 배경 오브젝트
    GetObjectManager().CreateGameObject<GameOverBackgroundObject>();

    // 게임오버 전, 마지막 스크린샷 화면을 표시하는 오브젝트
    GetObjectManager().CreateGameObject<GameOverScreenCaptureDisplayObject>();

    // TODO: 점수 표시하기
    // TODO: 최고점수 표시하기

    GetObjectManager().CreateGameObject<GameOverButtonsObject>();
}

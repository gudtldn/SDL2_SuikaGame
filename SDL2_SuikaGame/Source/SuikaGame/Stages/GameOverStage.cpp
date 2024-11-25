#include "GameOverStage.h"
#include "SuikaGame/GameObjects/GameOverScreenCaptureDisplayObject.h"


void GameOverStage::InitializeStage()
{
    // 게임오버 전, 마지막 스크린샷 화면을 표시하는 오브젝트
    GetObjectManager().CreateGameObject<GameOverScreenCaptureDisplayObject>();
}

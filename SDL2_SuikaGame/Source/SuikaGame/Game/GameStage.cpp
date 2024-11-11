#include "GameStage.h"
#include "BorderBackgroundObject.h"
#include "BorderObject.h"


GameStage::GameStage(GameEngine* engine)
    : Stage(engine)
{
    GetObjectManager().CreateGameObject<BorderBackgroundObject>();
    GetObjectManager().CreateGameObject<BorderObject>();
}

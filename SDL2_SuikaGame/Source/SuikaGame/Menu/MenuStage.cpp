#include "MenuStage.h"
#include "MenuBackgoundObject.h"
#include "StartButtonObject.h"


MenuStage::MenuStage(GameEngine* engine)
    : Stage(engine)
{
    GetObjectManager().AddGameObject<MenuBackgoundObject>();
    GetObjectManager().AddGameObject<StartButtonObject>();
}

#include "MenuStage.h"
#include "MenuBackgoundObject.h"


MenuStage::MenuStage(GameEngine* engine)
    : Stage(engine)
{
    GetObjectManager().AddGameObject<MenuBackgoundObject>();
}

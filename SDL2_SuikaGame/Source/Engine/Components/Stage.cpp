#include "Stage.h"
#include "Engine/GameEngine.h"


Stage::Stage(GameEngine* engine)
    : engine(engine)
    , object_manager(engine)
{
}

#include "Stage.h"
#include "GameEngine.h"


Stage::Stage(GameEngine* engine)
    : engine(engine)
    , object_manager(engine)
{
}

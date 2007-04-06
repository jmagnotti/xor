#include "KeyHandler.h"


/**
 * Default Constructor
 */
KeyHandler::KeyHandler(Controller * ctrl)
{
    _controller = ctrl; 
    _controller->getKeyboard()->addListener(this);

    _vectors["UP"]      = new Vector3D(0,1,0);
    _vectors["DOWN"]    = new Vector3D(0,-1,0);
    _vectors["RIGHT"]   = new Vector3D(-1,0,0);
    _vectors["LEFT"]    = new Vector3D(1,0,0);
    _vectors["IN"]      = new Vector3D(0,0,1);
    _vectors["OUT"]     = new Vector3D(0,0,-1);

    _timers["1"] = new TimedInterpolation(3000, NULL);
    _timers["2"] = new TimedInterpolation(2000, NULL);
    _timers["1/10"] = new TimedInterpolation(100, NULL);
    _timers["10"] = new TimedInterpolation(10000, NULL);
}

/**
 * moves the camera up by 1 over 1 second
 */
void KeyHandler::handleKey_e()
{
    _controller->getCamera()->incrementTranslation(_vectors["UP"], _timers["1"]);
}

void KeyHandler::handleKey_c()
{
    _controller->getCamera()->incrementTranslation(_vectors["DOWN"], _timers["1"]);
}

void KeyHandler::handleKey_d()
{
    _controller->getCamera()->incrementTranslation(_vectors["RIGHT"], _timers["1"]);
}

void KeyHandler::handleKey_a()
{
    _controller->getCamera()->incrementTranslation(_vectors["LEFT"], _timers["1"]);
}

void KeyHandler::handleKey_w()
{
    _controller->getCamera()->incrementTranslation(_vectors["IN"], _timers["1"]);
}

void KeyHandler::handleKey_s()
{
    _controller->getCamera()->incrementTranslation(_vectors["OUT"], _timers["1"]);
}

void KeyHandler::handleKey_P()
{
    ((DebugCamera*)_controller->getCamera())->debug();
}

void KeyHandler::handleKey_D()
{
    _controller->getCamera()->incrementFocalPoint(_vectors["RIGHT"], _timers["10"]);
}

void KeyHandler::handleKey_A()
{
    _controller->getCamera()->incrementFocalPoint(_vectors["LEFT"], _timers["10"]);
}


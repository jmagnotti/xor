#include "DebugCamera.h"


namespace XOR {

DebugCamera::~DebugCamera()
{}


/**
 * Constructs the real viewer
 */
DebugCamera::DebugCamera()
{
    cout <<"cstr" << endl;
    _interval = 2000;
}


/**
 * Prints out status information every 5 seconds
 */
void DebugCamera::renderObject()
{
    if (isReady()) {
        debug();
        _lastPrint = Controller::GetInstance(NULL)->getTimer()->getElapsedTime();
    }

    Camera::renderObject();
}


/**
 * Prints out information about each of the coordinate systems.
 */
void DebugCamera::debug()
{
    //print();
    _coordinateSystem->print();
}


/**
 * Returns whether the amount of time since the last debug is greater than the established debug interval.
 */
bool DebugCamera::isReady()
{
    return Controller::GetInstance(NULL)->getTimer()->getElapsedTime() - _lastPrint > _interval;
}


/**
 * @param interval  The interval (in milliseconds) that must elapse before each debug prinout.
 */
void DebugCamera::setDebugInterval(int interval)
{
    _interval = interval;
}


}


#include "DebugViewer.h"


namespace XOR {

DebugViewer::~DebugViewer()
{}


/**
 * Constructs the real viewer
 */
DebugViewer::DebugViewer()
{
    cout <<"cstr" << endl;
    _interval = 2000;
}


/**
 * Prints out status information every 5 seconds
 */
void DebugViewer::view()
{
    if (isReady()) {
        debug();
        _lastPrint = Controller::GetInstance(NULL)->getTimer()->getElapsedTime();
    }

    Viewer::view();
}


/**
 * Prints out information about each of the coordinate systems.
 */
void DebugViewer::debug()
{
    print();
    _coordinateSystem->print();
}


/**
 * Returns whether the amount of time since the last debug is greater than the established debug interval.
 */
bool DebugViewer::isReady()
{
    return Controller::GetInstance(NULL)->getTimer()->getElapsedTime() - _lastPrint > _interval;
}


/**
 * @param interval  The interval (in milliseconds) that must elapse before each debug prinout.
 */
void DebugViewer::setDebugInterval(int interval)
{
    _interval = interval;
}


}


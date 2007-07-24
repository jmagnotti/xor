#ifndef DEBUGVIEWER_H
#define DEBUGVIEWER_H


#include <iostream>
#include "Camera.h"
#include "Controller.h"
#include "../event/timer/Timer.h"

using namespace std;

namespace XOR {

/**
 * Prints out coordinate system information at a given interval.
 */
class DebugCamera : public Camera
{

public:

    /**
     * Constructs the real viewer
     */
    DebugCamera();


    /**
     * Prints out information about each of the coordinate systems.
     */
    void debug();


    /**
     * Returns whether the amount of time since the last debug is greater than
     * the established debug interval.
     */
    bool isReady();


    /**
     * @param interval  The interval (in milliseconds) that must elapse before
     * each debug prinout.
     */
    void setDebugInterval(int interval);

    void renderObject();

    ~DebugCamera();


private:

	int _interval;
	int _lastPrint;
};

}

#endif			// DEBUGVIEWER_H


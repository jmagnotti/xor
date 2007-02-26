#ifndef DEBUGVIEWER_H
#define DEBUGVIEWER_H


#include <iostream>
#include "Viewer.h"
#include "Controller.h"
#include "../event/timer/Timer.h"

using namespace std;

namespace XOR {

/**
 * Prints out coordinate system information at a given interval.
 */
class DebugViewer : public Viewer
{

public:

    /**
     * Constructs the real viewer
     */
    DebugViewer();


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


    /**
     * Prints out status information every 5 seconds in addition to rendering the model.
     */
    void view();


    ~DebugViewer();


private:

	int _interval;
	int _lastPrint;
};

}

#endif			// DEBUGVIEWER_H


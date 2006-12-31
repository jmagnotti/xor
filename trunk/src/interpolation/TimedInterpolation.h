#ifndef TIMEDINTERPOLATOR_H
#define TIMEDINTERPOLATOR_H


#include "../event/Timer.h"
#include "../event/TimerListener.h"
#include "InterpolationListener.h"
#include "InterpolationEngine.h"


namespace XOR {

/**
 * This class defines an interface for interpolators that are controlled by timer ticks instead of
 * successive calls to next(). If you create an interpolation whose time is less than one frame,
 * an interpolation with 0 steps will be created.
 */
class TimedInterpolation : public InterpolationEngine, public TimerListener
{

public:


    /**
     * Explicit Constructor
     */
    TimedInterpolation(int milliseconds, InterpolationListener * listener = NULL);


    /** 
     * Calls next()
     */
    virtual void handleTick();

 
    /**
     * Takes care of notifying listeners and removing itself as a timer listener
     */
    virtual void notifyAll();


    /**
     * Starts the interpolator
     */
    void start(void);



protected:

    int _time;

};

}

#endif          // TIMEDINTERPOLATOR_H


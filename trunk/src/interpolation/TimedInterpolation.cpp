#include "TimedInterpolation.h"


namespace XOR {

/*
 * Setup a timed interpolation
 */
TimedInterpolation::TimedInterpolation(int milliseconds, InterpolationListener * listener)
{
    _time = milliseconds;

    _iterationsRemaining = (int)(_time/(double)Timer::GetInstance()->getInterval());

    addListener(listener);
}


/*
 * Increment the interpolable
 */
void TimedInterpolation::handleTick()
{
    next();
}


/**
 * Send notifications to listeners and stop listening to the timer
 */
void TimedInterpolation::notifyAll()
{
    InterpolationEngine::notifyAll();
    Timer::GetInstance()->removeListener(this);
}


/*
 * Adds itself to the timer to start the next() calls
 */
void TimedInterpolation::start()
{
    Timer::GetInstance()->addListener(this);
}

}

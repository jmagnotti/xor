#include "TimedInterpolation.h"


namespace XOR {

/*
 * Setup a timed interpolation
 */
TimedInterpolation::TimedInterpolation(Interpolable * start, Positionable * finish, int milliseconds)
{
     _time = milliseconds;
    _current = start;

    _iterationsRemaining = _time/(double)Timer::GetInstance()->getInterval();

    _current->scale(finish, _iterationsRemaining);
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


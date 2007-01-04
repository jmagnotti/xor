#include "TimedInterpolation.h"


namespace XOR {

/*
 * Setup a timed interpolation
 */
TimedInterpolation::TimedInterpolation(int milliseconds, InterpolationListener * listener)
{
    cout << "Amount of time for interpolating: " << milliseconds << endl;

    _time = milliseconds;
    _size = _iterationsRemaining = (int)(_time/(double)Timer::GetInstance()->getInterval());

    _iterationsRemaining = (int)(_time/(double)Timer::GetInstance()->getInterval());
    cout << "Time: " << milliseconds << ", adjusted for interval of " <<
            Timer::GetInstance()->getInterval() << " resolves to " << _iterationsRemaining << " number of steps."  << endl;

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

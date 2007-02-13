#include "TimedInterpolation.h"


namespace XOR {

/*
 * Setup a timed interpolation
 */
TimedInterpolation::TimedInterpolation(int milliseconds, InterpolationListener * listener)
{
    //cout << "Amount of time for interpolating: " << milliseconds << endl;

    Timer * timer = Controller::GetInstance()->getTimer();

    _time = milliseconds;
    _size = _iterationsRemaining = (int)(_time/(double)timer->getInterval());

    _iterationsRemaining = (int)(_time/(double)timer->getInterval());

    //cout << "Time: " << milliseconds << ", adjusted for interval of " << timer->getInterval() << " resolves to " << _iterationsRemaining << " number of steps."  << endl; 
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
    Controller::GetInstance()->getTimer()->removeListener(this);
}


/*
 * Adds itself to the timer to start the next() calls
 */
void TimedInterpolation::start()
{
    Controller::GetInstance()->getTimer()->addListener(this);
}

}


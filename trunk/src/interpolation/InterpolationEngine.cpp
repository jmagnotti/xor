#include "InterpolationEngine.h"


namespace XOR {

/*
 * Explicit Constructor
 */
InterpolationEngine::InterpolationEngine(int steps, InterpolationListener * listener)
{
    _iterationsRemaining = steps;
    addListener(listener);
}


/*
 * Destructor
 */
InterpolationEngine::~InterpolationEngine()
{
    _listeners.clear();
}


/*
 * Add a listener to the pool
 */
void InterpolationEngine::addListener(InterpolationListener * listener)
{
    if (listener != NULL)
        _listeners.push_back(listener);
}


/**
 * Returns the current interpolable
Interpolable * InterpolationEngine::getCurrentInterpolation()
{
    return _current; 
}

 */

/*
 * procedes to the next iteration
 */
void InterpolationEngine::next()
{
    if (_iterationsRemaining <= 0) {
        notifyAll();
    }
    else {
        --(_iterationsRemaining);
    }
}


/*
 * Tells all listeners that the iteration is complete
 */
void InterpolationEngine::notifyAll()
{
    vector<InterpolationListener*>::iterator iter    = _listeners.begin();
    vector<InterpolationListener*>::iterator finish  = _listeners.end();

    while (iter != finish) {
        (*iter)->interpolationComplete();
        ++iter;        
    }
}

}


#include "InterpolationEngine.h"


namespace XOR {

/*
 * Explicit Constructor
 */
InterpolationEngine::InterpolationEngine(Interpolable * start, Positionable * finish, int steps)
{
    _current = start;
    _current->scale(finish, _iterationsRemaining);

    _iterationsRemaining = steps;
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
    if (listener != 0)
        _listeners.push_back(listener);
}


/**
 * Returns the current interpolable
 */
Interpolable * InterpolationEngine::getCurrentInterpolation()
{
    return _current; 
}


/*
 * procedes to the next iteration
 */
void InterpolationEngine::next()
{
    if (_iterationsRemaining <= 0) {
        notifyAll();
    }
    else {
        _current->next();
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


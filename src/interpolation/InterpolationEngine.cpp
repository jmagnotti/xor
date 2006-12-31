#include "InterpolationEngine.h"


namespace XOR {

/*
 * Explicit Constructor
 */
InterpolationEngine::InterpolationEngine(int steps, InterpolationListener * listener)
{
    _interpolator = InterpolatorFactory::GetInstance()->getDefaultInterpolator();
    _iterationsRemaining = _size = steps;
    
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
    _interpolator->next();
        
    // decrement and check for completion
    if (--_iterationsRemaining <= 0)
        notifyAll();
        
}


/*
 * setup up the interpolation
 */
void InterpolationEngine::setup(vector <float*> & in, vector <float*> & out)
{
    _interpolator->setScale(in, out, _size);
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


void InterpolationEngine::setInterpolator(const int interpolator)
{
    if (_interpolator->getType() != interpolator) {
        delete _interpolator;
        _interpolator = InterpolatorFactory::GetInstance()->getInterpolator(interpolator);
    }
}

}


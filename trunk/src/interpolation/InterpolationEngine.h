#ifndef INTERPOLATIONENGINE_H
#define INTERPOLATIONENGINE_H


#include <vector>

#include "InterpolationListener.h"

using namespace std;

namespace XOR {


/**
 * This class defines a high-level parent for all interpolators. This class allows for generic 
 * incrementing of an Interpolable. The details of how the incrementing is done is left to the
 * underlying Interpolable object.
 */
class InterpolationEngine
{

public:
    

    /**
     * Explicit Constructor
     */
    InterpolationEngine(int, InterpolationListener * listener=NULL);


    /**
     * Destructor
     */
    virtual ~InterpolationEngine(void);

 
    /**
     * Adds a listener to the collection
     */
    virtual void addListener(InterpolationListener *);


    /**
     * Delegates to the underlying interpolable.
     */
    virtual void next(void);


    /**
     * Starts the interpolator
     */
    virtual void start(void)=0;


protected:

    /**
     * Tells all listeners that the iteration is complete
     */
    virtual void notifyAll();

    vector<InterpolationListener*> _listeners;

    int _iterationsRemaining;

    // shouldn't be using the default constructor.
    InterpolationEngine(void)
    {}


};

}

#endif          // INTERPOLATIONENGINE_H


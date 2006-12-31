#ifndef INTERPOLATIONENGINE_H
#define INTERPOLATIONENGINE_H


#include <vector>

#include "InterpolationListener.h"
#include "Interpolator.h"
#include "InterpolatorFactory.h"

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
     * Adds a listener to the collection. Subclasses do not need to check for NULL, as this 
     * method does its own checking.
     * 
     * @param listener  An object to notify upon completion of the interpolation
     */
    virtual void addListener(InterpolationListener * listener);


    /**
     * Delegates to the underlying interpolable.
     */
    virtual void next(void);


    /**
     * Connects the interpolator with the values
     * Collections are automatically passed by reference, so we don't need to declare them as pointers.
     */
     virtual void setup(vector <float*> & in, vector <float*> & out);


    /**
     * Changes the interpolator for the engine.
     * 
     * Subclasses may need to treat this specially if they need are going to 
     * swap out interpolator's midstream. Consult the child class for exact 
     * specification of when the interpolator is switched out. The default 
     * implementation sets the interpolator if and only if 
     * _iterationsRemaining is <= 0.
     * 
     * @param interpolator  The interpolator to use with this engine. The 
     *  constant is used here instead of the actual interpolator so we 
     *  can abstract the memory management from the user. We may want 
     *  to reuse the interpolators, and we want to avoid ambiguous memory 
     *  allocation/deallocation contracts.
     */
    virtual void setInterpolator(const int interpolator);
             

    /**
     * Starts the interpolator
     */
    virtual void start(void)=0;


protected:


    /**
     * Tells all listeners that the iteration is complete
     */
    virtual void notifyAll();


    /*
     * Needed for child classes?
     */
    InterpolationEngine()
    {}


    vector<InterpolationListener*> _listeners;
    
    Interpolator * _interpolator;

    int _size, _iterationsRemaining;

};

}

#endif          // INTERPOLATIONENGINE_H


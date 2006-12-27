#ifndef INTERPOLATOR_H
#define INTERPOLATOR_H


#include <list>


using namespace std;

namespace XOR {

/**
 * This class defines a high-level parent for all interpolators. The details of how the
 * incrementing is done is left to the underlying Interpolator object. This is
 * not to be used for objects that may be colliding with other objects. A more
 * high performance implementation is needed for that. Look to the particle
 * class (which may not be implemented yet).
 */
class Interpolator
{

public:

    /**
     * Because the interpolator has a reference to the original values, they do
     * not need to be passed in.
     */
    virtual void next()=0;


    /**
     * Reset the interpolator. This clears out the step amounts and the stored values. 
     */
    void reset(void);


    /**
     * Call this to scale values
     */
    virtual void setScale(list <float*> * in, list <float*> * out, int
            numSteps)=0;


    /**
     * Call this to scale values
     */
    virtual void setScale(float & in, float & out, int numSteps)=0;
     

protected:
    
    list <float> * _steps;
    list <float*> * _values;

};

}

#endif          // INTERPOLATOR_H


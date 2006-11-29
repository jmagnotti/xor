#ifndef INTERPOLATOR_H
#define INTERPOLATOR_H


#include <vector>

#include "Interpolable.h"
#include "../shape/Positionable.h"


namespace XOR {

using namespace std;

/**
 * This class defines a high-level parent for all interpolators. This class allows for generic 
 * incrementing of an Interpolable. The details of how the incrementing is done is left to the
 * underlying Interpolable object. This is not to be used for objects that may be colliding with other objects. A more high performance implementation is needed for that. Look to the particle class (which may not be implemented yet).
 */
class Interpolator
{

public:
    
 
    /**
     * Advances the interpolation
     */
    virtual void next(float &)=0;


    /**
     * Sets up the interpolator
     */
    virtual void setScale(float &, float &, int)=0;
     

protected:
    
    float _current, _step;

};

}

#endif          // INTERPOLATOR_H


#ifndef INTERPOLABLE_H
#define INTERPOLABLE_H


#include "../shape/Positionable.h"


namespace XOR {

/**
 * This class define an interface to what it means to be interpolable.
 * This class is used by the interpolator to generate a sequence of instances based on a given 
 * beginning instance and ending position.
 * This is a pretty volatile piece of code, the API has not yet been finalized.
 */
class Interpolable : public Positionable
{

public: 


    /**
     * This is called by the InterpolationEngine. 
     */
    virtual void next(void)=0;


    /**
     * Used to determine when the values are close enough to be considered equal
     */
    virtual bool compare(Positionable *)=0;


    /**
     * Sets up the underlying Interpolator
     */
    virtual Positionable * scale(Positionable *, int)=0;


    /**
     * At the end of an interpolation, it is common to set the value of the Positionable
     */
    virtual void set(Positionable *, bool alias=false)=0;


};

}

#endif          // INTERPOLABLE_H


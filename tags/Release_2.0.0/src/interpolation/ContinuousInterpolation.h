#ifndef CONTINUOUSINTERPOLATION_H
#define CONTINUOUSINTERPOLATION_H


#include "TimedInterpolation.h"

namespace XOR {

/**
 * This class defines an interpolator that provides a looping Interpolation. Upon
 * reaching the end of the sequence the interpolator can either start over, or 
 * step backward through the interpolated steps. Interpolation only stops when the
 * stop method is called. The repeat type can be reset on the fly, but only takes affect
 * upon reaching the end of a sequence.
 * 
 * @author John Magnotti
 * @version 1.0
 */
class ContinuousInterpolation : public TimedInterpolation
{

public:
    
    ContinuousInterpolation(int i, InterpolationListener *l)
    {}
    
    
    /**
     * Upon reaching the end of the sequence, the interpolation restarts at at the first instance.
     */
    static const int CYCLICAL   = 0;


    /**
     * Upon reaching the end of the sequence, the interpolation goes backward through the instances.
     */
    static const int REGRESSIVE = 1;
    

    /**
     * Starts the interpolator
     */
    virtual void start();
    
    
    /**
     * Stops the interpolator
     */
    virtual void stop();

    
    /**
     * Sets the repeat method
     */
    virtual void setRepeatType(int type) {   _repeatType = type;  }


protected:
    
    int     _repeatType;

    virtual void resetInterpolation();
    
};

}

#endif          // CONTINUOUSINTERPOLATION_H


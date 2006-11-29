#ifndef LINEARINTERPOLATOR_H
#define LINEARINTERPOLATOR_H


#include "Interpolator.h"


namespace XOR {

/**
 * Encapsulates a linear interpolator
 */
class LinearInterpolator : public Interpolator
{

public:

    /**
     * Default Constructor
     */
    LinearInterpolator()
    {
        _step = 0;
    }


    /**
     * Calculates the next value in the sequence and stores it in value
     */
    void next(float & value)
    {
       value += _step; 
    }

   
   /**
    * Calculates the step amount
    */ 
    void setScale(float & begin, float & end, int steps)
    {
        _step = (end - begin) / steps;
    }

};

}

#endif          // LINEARINTERPOLATOR_H


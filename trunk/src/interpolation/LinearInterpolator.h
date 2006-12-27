#ifndef LINEARINTERPOLATOR_H
#define LINEARINTERPOLATOR_H

#include<list>
#include <iostream>

#include "Interpolator.h"
#include "../util/GraphicsConversionUtility.h"

using namespace std;

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
    LinearInterpolator();


    /**
     * Calculates the next value in the sequence and stores it in value
     */
    void next(void);


    /**
     * Reset the interpolation
     */
    void reset(void);
   
    /**
     * Calculates the step amount
     */
    void setScale(float & in, float & out, int numSteps);
    void setScale(list <float*> * in, list <float*> * out, int numSteps);


};

}

#endif          // LINEARINTERPOLATOR_H


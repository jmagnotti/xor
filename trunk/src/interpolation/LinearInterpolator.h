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


    /*
     * ensures that the interpolation is complete
     */
    void finish(void);
    
   
    /**
     * Calculates the step amount
     */
    void setScale(vector <float*> & in, vector<float> & out, int numSteps);


    /**
     * Returns the type.
     * 
     * @return The constant defining this interpolator (i.e. Interpolator::LINEAR_INTERPOLATOR).
     */
    const int getType();
    
    
};

}

#endif          // LINEARINTERPOLATOR_H


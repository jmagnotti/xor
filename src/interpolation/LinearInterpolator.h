#ifndef LINEARINTERPOLATOR_H
#define LINEARINTERPOLATOR_H

#include<list>
#include<vector>
#include <iostream>

#include "Interpolator.h"
#include "../util/GraphicsConversionUtility.h"
#include "../geometry/Vector3D.h"


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
     *
     */
    vector<Vector3D*> build(Vector3D * target, int numSteps);


    /**
     * Returns the type.
     * 
     * @return The constant defining this interpolator (i.e. Interpolator::LINEAR_INTERPOLATOR).
     */
    const int getType();
    

private:

    vector<Vector3D*> _steps;
    
};

}

#endif          // LINEARINTERPOLATOR_H


#ifndef INTERPOLATOR_H
#define INTERPOLATOR_H


#include <vector>
#include "../geometry/Vector3D.h"


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

    /*
     * Interpolator Constants. Used to specify which interpolator to retrieve or 
     * which to set as the default for the InterpolatorFactory.
     * 
     * @see Paint for a discussion about initializing static const class data in the Header file.
     */
    static const int SQ_ROOT_INTERPOLATOR   = -1;
    static const int RK4_INTERPOLATOR       = 0;
    static const int LINEAR_INTERPOLATOR    = 1;
    static const int SQUARED_INTERPOLATOR   = 2;
    static const int CUBIC_INTERPOLATOR     = 3;


    // used by Transforms
    virtual vector<Vector3D*> * build(Vector3D * target, int numSteps)=0;
    virtual vector<float> * build(float target, int numSteps)=0;

    /**
     * Because the interpolator has a reference to the original values, they do
     * not need to be passed in.
     */
    virtual void next()=0;


    /**
     * Reset the interpolator. This clears out the step amounts and the stored values. 
     */
    virtual void reset(void)=0;


    /**
     * Call this to scale values
     */
    virtual void setScale(vector <float*> & in, vector <float> & out, int numSteps)=0;


    /*
     * guarantee that in[i] == out[i]. This is especially important when dealing with floats.
     */
    virtual void finish()=0;
    

    /**
     * Returns one of the constants above.
     */
    virtual const int getType()=0;


protected:

    //vector <Vector3D> * _steps, * _final;
    //vector <float*> * _values;

};

}

#endif          // INTERPOLATOR_H


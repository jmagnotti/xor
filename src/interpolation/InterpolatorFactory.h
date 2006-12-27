#ifndef INTERPOLATORFACTORY_H
#define INTERPOLATORFACTORY_H

#include <iostream>

#include "Interpolator.h"
#include "LinearInterpolator.h"
//#include "ExponentialInterpolator.h"

using namespace std;

namespace XOR {

/**
 * Easy way to create Interpolators
 */
class InterpolatorFactory
{
    
public:

    static const int SQ_ROOT_INTERPOLATOR   = -1;
    static const int RK4_INTERPOLATOR       = 0;
    static const int LINEAR_INTERPOLATOR    = 1;
    static const int SQUARED_INTERPOLATOR   = 2;
    static const int CUBIC_INTERPOLATOR     = 3;

    
    /**
     * Singleton Accessor for the factory
     */
    static InterpolatorFactory * GetInstance();


    /**
     * Returns the interpolator that is currently set as the deafult.
     * The default is LINEAR, change it with setDefaultInterpolator.
     */
    Interpolator * getDefaultInterpolator();

    /**
     * Sets the interpolator that will be used by default
     */
    void setDefaultInterpolator(int interpolator);


    /**
     * Provides a way to create interpolators 
     */
    Interpolator * getInterpolator(int interpolator);

protected:

    InterpolatorFactory();


private:

    int _defaultInterpolator;

    static InterpolatorFactory * _interpolatorFactory;

};

}

#endif          // INTERPOLATORFACTORY_H


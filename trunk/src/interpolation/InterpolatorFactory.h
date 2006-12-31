#ifndef INTERPOLATORFACTORY_H
#define INTERPOLATORFACTORY_H

#include <iostream>

#include "Interpolator.h"
#include "LinearInterpolator.h"
//#include "ExponentialInterpolator.h"

using namespace std;

namespace XOR {

/**
 * Easy way to create Interpolators. Additionally, this factory is used by the 
 * InterpolationEngines to retrieve an interpolator. Applications should set 
 * the default interpolator at the beginning of their interpolation, to ensure 
 * that all InterpolationEngines use it.
 * 
 * @author John Magnotti, Michael Lam
 * @version 1.0
 */
class InterpolatorFactory
{
    
public:

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
    
    
    /**
     * Put the Interpolator back into the ready pool.
     * 
        void reclaimInterpolator(Interpolator * interpolator)
     */
    

protected:

    InterpolatorFactory();


private:

    int _defaultInterpolator;

    static InterpolatorFactory * _interpolatorFactory;

};

}

#endif          // INTERPOLATORFACTORY_H


#ifndef INTERPOLATIONLISTENER_H
#define INTERPOLATIONLISTENER_H


namespace XOR {

/**
 * This class defines an interface that allows classes to receive notification 
 * for when an interpolation is complete. Note that the exact specification of when this is called
 * is up to the interpolator.
 */
class InterpolationListener
{

public:

    /**
     * Called by the InterpolationEngine
     */
    virtual void interpolationComplete()=0;

};

}

#endif          // INTERPOLATIONLISTENER_H


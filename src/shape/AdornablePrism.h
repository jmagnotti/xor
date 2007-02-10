#ifndef ADORNABLEPRISM_H
#define ADORNABLEPRISM_H


#include "RectangularPrism.h"
#include "Object3D.h"


namespace XOR {


/**
 * Represents a solid that can have other 3D objects attached to it.
 */
class AdornablePrism : public RectangularPrism
{

public:
    
    /**
     * Explicit Constructor
     */
    AdornablePrism(RectangularVolume * volume);


    /**
     * Sets the decoration on the given wall
     */
    void setAdornment(Object3D * adornment, const int face);


protected:

    /**
     * Renders the adorned prism
     */
    void render();


	/**
	 * Convenience for specializations, like AdornableCube
	 */
	AdornablePrism();

private:

    // Will store pointers to the renderables that need to be drawn on the walls
    Object3D * _adornments[6];

};

}

#endif      // ADORNABLEPRISM_H

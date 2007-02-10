#include "AdornablePrism.h"

namespace XOR {


/*
 * explicit constructor
 */
AdornablePrism::AdornablePrism(RectangularVolume * volume) :
	RectangularPrism(volume)
{}


/*
 * Sets the renderable to "attach" to a wall
 */
void AdornablePrism::setAdornment(Object3D * adornment, const int face)
{
    // think about how this should be implemented
}


/*
 * renders the adornable prism
 */
void AdornablePrism::render(void)
{
    RectangularPrism::render();

    //now render the adornment
}

}


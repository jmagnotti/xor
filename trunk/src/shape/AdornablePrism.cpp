#include "AdornablePrism.h"

namespace XOR
{

/*
 * explicit constructor
 */
AdornablePrism::AdornablePrism(RectangularVolume * volume) :
    RectangularPrism(volume)
{
    _adornments = new Object3DCollection();
}

AdornablePrism::AdornablePrism(Vector3D * origin, Dimension3D * size, Paint * p) :
    RectangularPrism(origin, size, p)
{
}

/*
 * Sets the renderable to "attach" to a wall
 */
void AdornablePrism::setAdornment(Object3D * adornment, const int face)
{
}

/*
 * renders the adornable prism
 */
void AdornablePrism::renderObject()
{
    RectangularPrism::renderObject();

    //now render the adornment
}

}


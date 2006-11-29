#include "AdornablePrism.h"

namespace XOR {

/*
 * Sets the renderable to "attach" to a wall
 */
void AdornablePrism::setAdornment(Renderable * rend, int wall)
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


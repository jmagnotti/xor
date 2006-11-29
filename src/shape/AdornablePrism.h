#ifndef ADORNABLEPRISM_H
#define ADORNABLEPRISM_H


#include "RectangularPrism.h"
#include "Renderable.h"

namespace XOR {


class AdornablePrism : public RectangularPrism
{

public:

    /**
     * Default Constructor
     */
    AdornablePrism()
    {
        RectangularPrism::RectangularPrism();
    }

    
    /**
     * Explicit Constructor
     */
    AdornablePrism(RectangularVolume * vol)
    {
      //  RectangularPrism::RectangularPrism(vol);
    }


    /**
     * Sets the decoration on the given wall
     */
    void setAdornment(Renderable *, int);


    /**
     * Renders the adorned prism
     */
    void render(void);
    

protected:

    // Will store pointers to the renderables that need to be drawn on the walls
    Renderable * _adornments[6];

};

}

#endif      // ADORNABLEPRISM_H

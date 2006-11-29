#ifndef ADORNABLECUBE_H
#define ADORNABLECUBE_H


#include "Cube.h"
#include "AdornablePrism.h"
namespace XOR {

/**
 * A convenience class. All work is delegated, including construction
 */
class AdornableCube : public Cube, public AdornablePrism
{
    AdornableCube();


    AdornableCube(Point3D* point, float rad, Paint *p);

    
    void render(void);

};


}
#endif // ADORNABLECUBE_H

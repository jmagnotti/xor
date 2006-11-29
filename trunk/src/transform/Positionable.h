#ifndef POSITIONABLE_H
#define POSITIONABLE_H


#include "../geometry/Dimension3D.h"
#include "../shape/Point3D.h"


namespace XOR {

/**
 * A class that provides an interface to objects that can be positioned in 3D space.
 */
class Positionable
{

public:

    /**
     * Access to a point that defines f(minX, minY, minZ)
     */
    virtual Point3D * getRegistrationPoint()=0;


    /**
     * Dimension object that defines the size of the object. This returns a pointer for effiency, 
     * and it is intended that the caller will not modify this reference.
     */
    virtual Dimension3D * getDimension()=0;


};

}

#endif          // POSITIONABLE_H


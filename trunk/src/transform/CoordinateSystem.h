#ifndef COORDINATESYSTEM_H
#define COORDINATESYSTEM_H


#include "Transform.h"
#include "Rotate.h"


namespace XOR {

/**
 *
 */
class CoordinateSystem : public Transform
{

public:

    /**
     * Applies the coordinate system transforms
     */
    virtual void push();


    /**
     * Removes the coordinate system transforms
     */
    virtual void pop();

    /**
     * Here for completeness, but this method is empty. It doesn't make any
     * sense to clear a coordinate system.
     */
    void clear();


protected:

    Rotate  * _rotations[3];

    CoordinateSystem();

};

}

#endif          // COORDINATESYSTEM_H


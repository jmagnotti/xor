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
    void push();


    /**
     * Removes the coordinate system transforms
     */
    void pop();


protected:

    Rotate  * _xRotation, 
            * _yRotation,
            * _zRotation;

    CoordinateSystem();

};

}

#endif          // COORDINATESYSTEM_H


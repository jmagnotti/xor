#ifndef COORDINATESYSTEM_H
#define COORDINATESYSTEM_H


#include "Transform.h"
#include "Rotate.h"
#include "Scale.h"


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
    virtual void pushInverse();

    virtual void transform(Vector3D * position);
    virtual void transform(Dimension3D * size);

    /**
     * Removes the coordinate system transforms
     */
    virtual void pop();

    /**
     * Here for completeness, but this method is empty. It doesn't make any
     * sense to clear a coordinate system.
     */
    void toIdentity();


    virtual void print();


protected:

    Rotate  * _rotations[3];
	Scale   * _scale;

    CoordinateSystem();

};

}

#endif          // COORDINATESYSTEM_H


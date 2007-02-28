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


    /**
     * Removes the coordinate system transforms
     */
    virtual void pop();

    /**
     * Here for completeness, but this method is empty. It doesn't make any
     * sense to clear a coordinate system.
     */
    void clear();


    virtual void print();


protected:

    Rotate  * _rotations[3];
	Scale   * _scale;

	// on PPC/Mac the z-axis is inverted
	Scale   * _zInvertScale;

    CoordinateSystem();

};

}

#endif          // COORDINATESYSTEM_H


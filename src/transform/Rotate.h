#ifndef ROTATE_H
#define ROTATE_H

#include <vector>
#include <iostream>
#include <stdio.h>

#include "Transform.h"

#include "../geometry/Dimension3D.h"
#include "../interpolation/InterpolationEngine.h"
#include "../util/GraphicsConversionUtility.h"

using namespace std;

namespace XOR {

/**
 * Applies a rotate transform
 */
class Rotate : public Transform
{

public:


    /**
     * Default Constructor
     */
    Rotate();



	/**
	 * Explicit Constructor
	 */
	Rotate(float angle, int x, int y, int z);


    /**
     * Clones the values from one rotate to another
     */
    void clone(Rotate *);


	/**
	 * Applies the rotation
	 */
	void push(void);


	/**
	 * Applies the reverse rotation
	 */
	void pushInverse(void);
	

    /**
     * reset the rotate to have no effect
     */
    void toIdentity();

	void transform(Vector3D * position);
	void transform(Dimension3D * size);

    /**
     * 
     */
    void print();

protected:

    friend class Orientation;

	int		_xCoord, _yCoord, _zCoord;
	float	_angle;

    vector<float*> _values;
    vector<float> _out;

};

}

#endif			// ROTATE_H

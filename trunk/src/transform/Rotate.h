#ifndef ROTATE_H
#define ROTATE_H


#include "Transform.h"
#include "../geometry/Dimension3D.h"


namespace XOR {

/**
 * Applies a rotate transform
 */
class Rotate : public Transform
{
	friend class Positionable;

public:


    /**
     * Default Constructor
     */
    Rotate();


	/**
	 * Explicit Constructor
	 */
	Rotate(float, int, int, int);


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
	 * Easy way to increment a rotation
	 * to decrement, just increment by a negative amount
	 */
	void increment(Dimension3D*);


    /**
     * See Interpolable.h
    void scale(Interpolable * other, int numSteps);
     */


protected:

	int		_xCoord, _yCoord, _zCoord;
	float	_angle;

};

}

#endif			// ROTATE_H

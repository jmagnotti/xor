#ifndef ROTATE_H
#define ROTATE_H


#include "Transform.h"
#include "../geometry/Dimension3D.h"
#include "../interpolation/InterpolationEngine.h"


namespace XOR {

/**
 * Applies a rotate transform
 */
class Rotate : public Transform
{
    //trying to use this less and less. Performance tests should determine value    
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
	void increment(float angle, InterpolationEngine * interpolation=NULL);


    /**
     * Easy way to set a rotation
     * to decrement, just increment by a negative amount
     */
    void set(float angle, InterpolationEngine * interpolation=NULL);


protected:

	int		_xCoord, _yCoord, _zCoord;
	float	_angle;

};

}

#endif			// ROTATE_H

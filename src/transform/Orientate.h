#ifndef ORIENTATE_H
#define ORIENTATE_H


#include "Transform.h"
#include "../shape/Point3D.h"
#include "../util/GraphicsConversionUtility.h"
#include "Translate.h"
#include "Rotate.h"


namespace XOR {

/**
 * Applies a rotate transform
 */
class Orientate : public Transform
{

public:

	static const int THETA = 0;
	static const int PHI   = 1;
	static const int ROLL  = 2;

	/**
	 * Default Constructor
	 */
	Orientate();


	/**
	 * Explicit Constructors
	 */
	Orientate(Translate *, float, float, float);
	Orientate(Translate *, Translate *);


	/**
	 * Destructor
	 */
	~Orientate();


    /**
     * Copies the values from the other Orientate, no aliasing
     */
    void clone(Orientate *);


	/**
	 * Applies the transform
	 */
	void push(void);


	/**
	 * Applies the reverse transform
	 */
	void pushInverse(void);
	
	
	/**
	 * Removes the transform. Overridden because subtransforms need to be 
	 * popped in the reverse order that they are pushed. 
	 */
	void pop(void);


	/**
	 * Easy way to increment a position
	 * to decrement, just increment by a negative amount
	 */
	void incrementPosition(Point3D*);


	/**
	 * Easy way to increment the angle.
	 * Automatically adjusts rotations to match given
	 * theta, phi and roll angles.
	 * Dimensions: 0=theta,1=phi, 2=roll;
	 */
	void incrementRotation(int dimension, float angle);


	/**
	 * Easy way to set the focus point.
	 * Automatically adjusts rotations to match given point.
	 */
	void setFocalPoint(Point3D *point);


	/**
	 * Get the current value of a rotation
	 * Dimensions: 0=theta,1=phi, 2=roll;
	 */
	float getRotation(int dimension);
	
	/**
	 * Get a copy of the local focal point
	 * Remember to delete!
	 */
	Point3D * getFocalPoint();


	/**
	 * Easy way to move the camera a certain distance
	 * along its focus vector.
	 */
	void walk(float distance);


	/**
	 * Print all member info for debug purposes.
	 */
	void printDebugInfo();
	
	
protected:

	
	Translate * _position;
	Translate * _focalPoint;

	Rotate *	_theta;
	Rotate *	_phi;
	Rotate *	_roll;

	float       _focalDistance;

private:


	/**
	 * Update _focalPoint from translation
	 * and rotations.
	 */
	void updateFocalPoint();


	/**
	 * Update transforms from _focalPoint.
	 */
	void updateFromFocalPoint();


};

}

#endif			// ORIENTATE_H

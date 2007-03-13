#ifndef ORIENTATION_H
#define ORIENTATION_H

#include <vector>
#include <iostream>
#include <stdio.h>

#include "Transform.h"
#include "Transformable.h"
#include "../geometry/Dimension3D.h"
#include "../interpolation/InterpolationEngine.h"

using namespace std;

namespace XOR {

/**
 * Represents a "snapshot" of a Transformable object, storing a
 * translate and three rotates. An Orientation can be created from a
 * Transformable, and a Transformable can apply an Orientation using set
 * or increment methods. This class is also used by Waypoint in the
 * interpolation package to perform "path" interpolation.
 */
class Orientation : public Transform
{

public:


    /**
     * Default Constructor
     */
    Orientation();
    ~Orientation();


	/**
	 * Explicit Constructor
	 */
	Orientation(Translate *, Rotate *, Rotate *, Rotate *);


	/**
	 * Explicit Constructor
	 */
	Orientation(Orientation *);


	/**
	 * Explicit Constructor
	 */
	Orientation(Transformable *);


    /**
     * Clones the values from one Orientation to another
     */
	void clone(Orientation *);


	/**
	 * Applies the rotation
	 */
	void push(void);


	/**
	 * Applies the reverse rotation
	 */
	void pushInverse(void);


	/**
	 * Removes the transform.
	 */
	void pop();


	Translate * getTranslation();

	Rotate * getRotation(const int);


	/**
	 * Change one of the rotations
	 */
	void incrementRotation(const int, float, InterpolationEngine * interpolation=NULL);
    void setRotation(const int, float, InterpolationEngine * interpolation=NULL);

	/**
	 * Change the translate
	 */
	void incrementTranslation(Vector3D *, InterpolationEngine * interpolation=NULL);
	void setTranslation(Vector3D *, InterpolationEngine * interpolation=NULL);


	/**
	 * Apply the orientation to a Transformable object
	 */
	void incrementTransformable(Transformable *, InterpolationEngine * interpolation[4]);
	void setTransformable(Transformable *, InterpolationEngine * interpolation[4]);


    /**
     * reset the transform to have no effect
     */
    void clear();


    /**
     * 
     */
    void print();

protected:

	Translate * _position;
	Rotate    * _roll;
	Rotate    * _phi;
	Rotate    * _theta;
	Scale     * _scale;
	Stretch   * _stretch;
	Translate * _focalPoint;
	float		_focalDistance;
	bool		_transformed;
	bool        _deleteOnDispose;

};

}

#endif			// ORIENTATION_H

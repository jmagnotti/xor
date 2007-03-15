#ifndef ORIENTATION_H
#define ORIENTATION_H

#include <vector>
#include <iostream>
#include <stdio.h>

#include "Transform.h"
#include "Translate.h"
#include "Rotate.h"

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
     * Rotation Axis Constants.
     * Use these for any method that takes a Rotation and a const int axis.
     * They are declared in here so they can be used in switch statements.
     *
     * @see Paint   For a discussion on static constant class members in switch statements.
     */
	static const int THETA  = 0;
	static const int PHI    = 1;
	static const int ROLL   = 2;

    /**
     * Default Constructor
     */
    Orientation();
    ~Orientation();


	/**
	 * Explicit Constructor
	 * Build an Orientation from rotations and a position
	 */
	Orientation(Translate *, Rotate *, Rotate *, Rotate *);


	/**
	 * Explicit Constructor
	 * Build an Orientation from a position and a focal point
	 */
	Orientation(Translate *, Translate *);


	/**
	 * Explicit Constructor
	 * Build an Orientation as a copy of an existing orientation
	 */
	Orientation(Orientation *);


    /**
     * Clones the values from one Orientation to another
     */
	void clone(Orientation *);


    /**
	 * Returns a clone of the translation. The calling method is
	 * responsible for freeing memory associated with the returned
	 * Vector3D.
     */
    Vector3D * getTranslation();


    /**
     * Sets the translation for the object. This overrides whatever is set
     * currently. 
     * This is NOT a concatenation routine.
     *
     * @param position      A translate object that represents the new position
     *                      of the object.
     * @param interpolation An interapolation engine to be used to interpolate
     *                      the model change
     */
    void setTranslation(Vector3D * position);
    void setTranslation(Vector3D * position, InterpolationEngine * interpolation);


    /**
     * Increments the translation for the object. 
     * This is the a concatenation routine.
     *
     * @param position      A translate object that represents the new position
     *                      of the object.
     * @param interpolation An interapolation engine to be used to interpolate
     *                      the model change
     */
    void incrementTranslation(Vector3D * position);
    void incrementTranslation(Vector3D * position, InterpolationEngine * interpolation);


	/**
	 * Get the current value of a rotation
	 */
	float getRotation(const int dimension);


    /**
     * Sets the rotation for the given axis. axis must be one of 
     * Orientation::THETA, Orientation::PHI, or Orientation::ROLL. 
     * This is NOT a concatenation routine.
     *
     * @param angle         The new rotation angle.
     * @param axis          The axis upon which to rotate.
     * @param interpolation An interapolation engine to be used to interpolate
     *                      the model change.
     */
    void setRotation(const int axis, float angle);
    void setRotation(const int axis, float angle, InterpolationEngine * interpolation);


    /** 
     * Increments the rotation for the given axis. axis must be one of
     * Orientation::THETA, Orientation::PHI, or Orientation::ROLL.
     * This is the concatenation routine.
     *
     * @param angle         The new rotation angle.
     * @param axis          The axis upon which to rotate.
     * @param interpolation An interapolation engine to be used to interpolate
     *                      the model change.
     */
    void incrementRotation(const int axis, float angle);
    void incrementRotation(const int axis, float angle, InterpolationEngine * interpolation);


    /**
	 * Returns a Vector3D representation of the Scalar. Modifying this vector
	 * does not modify the Scale transform. The calling method is repsonsible
	 * for proper disposal of the Vector3D.
     */
    Vector3D * getScalar();


    /**
     * Sets the scale transformation. Note that this, like other transforms,
     * does not modify the actual parameters. 
     * This is NOT a concatenation routine.
     *
     * @param scalar        A Vector3D object with scalar values.
     * @param interpolation An interapolation engine to be used to interpolate
     *                      the model change.
     */
    void setScalar(Vector3D * scalar);
    void setScalar(Vector3D * scalar, InterpolationEngine * interpolation);


    /**
     * Increments the scalar value.
     * This is the concatenation routine.
     *
     * @param scalar        A Vector3D object with scalar values.
     * @param interpolation An interapolation engine to be used to interpolate
     *                      the model change.
     */
    void incrementScalar(Vector3D * scalar);
    void incrementScalar(Vector3D * scalar, InterpolationEngine * interpolation);


    /**
	 * Returns a Vector3D representation of the Stretch. Modifying this vector
	 * does not modify the Stretch transform. The calling method is repsonsible
	 * for proper disposal of the Vector3D.
     */
    Vector3D * getStretch();


    /**
     * Sets the stretch transformation. Note that this, like other transforms,
     * does not modify the actual parameters. 
     * This is NOT a concatenation routine.
     *
     * @param stretch        A Vector3D object with stretch values.
     * @param interpolation An interapolation engine to be used to interpolate
     *                      the model change.
     */
    void setStretch(Vector3D * stretch);
    void setStretch(Vector3D * stretch, InterpolationEngine * interpolation);


    /**
     * Increments the stretch vector.
     * This is the concatenation routine.
     *
     * @param stretch        A Vector3D object with stretch values.
     * @param interpolation An interapolation engine to be used to interpolate
     *                      the model change.
     */
    void incrementStretch(Vector3D * stretch);
    void incrementStretch(Vector3D * stretch, InterpolationEngine * interpolation);



    /**
	 * Returns the state of the transformed variable, which is set to TRUE when
	 * all transforms are at their default state.
     * 
     * @return Whether or not any of the transforms have been changed
     */
    bool isTransformed();


	/**
	 * Applies the transform
	 */
	void push();


	/**
     * Applies the inverse of each of the transforms. It delegates to the
     * underlying Rotate, Translate, or Scale object. Because the Scale
     * transform is rarely inverted, it is the special case to invert it
     *
     * @see Rotate, Translate, Scale For explanation of consequences of
     *      pushInverse.
	 */
	void pushInverse(bool invertScale=false);
	
	
	/**
	 * Removes the transform. Overridden because subtransforms need to be 
	 * popped in the reverse order that they are pushed. 
	 */
	void pop();

	
	/**
	 * Returns a Vector3D representation of the FocalPoint. Modifying this vector
	 * does not modify the FocalPoint. The calling method is repsonsible
	 * for proper disposal of the Vector3D.
	 */
	Vector3D * getFocalPoint();


	/**
	 * Easy way to set the focus point.
	 * Automatically adjusts rotations to match given point.
	 */
    void setFocalPoint(Vector3D * point);
    void setFocalPoint(Vector3D * point, InterpolationEngine * interpolation);


    void incrementFocalPoint(Vector3D * point);
    void incrementFocalPoint(Vector3D * point, InterpolationEngine * interpolation);


	/**
	 * Easy way to move the camera a certain distance
	 * along its focus vector.
	 */
	void walk(float distance, InterpolationEngine * interpolation);


	/**
	 * Print all member info for debug purposes.
	 */
	void print();
	

    /**
     * Remove the effect of all of the transform objects
     */
    void clear();

    
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
	void updateFromFocalPoint(InterpolationEngine * interpolation);

	Translate * _position;
	Rotate    * _roll;
	Rotate    * _phi;
	Rotate    * _theta;
	Translate * _focalPoint;
	float		_focalDistance;
	bool		_transformed;

};

}

#endif			// ORIENTATION_H
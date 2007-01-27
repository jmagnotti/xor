#ifndef POSITIONABLE_H
#define POSITIONABLE_H


#include "../../include/SDL_opengl.h"

#include "Transform.h"
#include "Scale.h"
#include "Translate.h"
#include "Rotate.h"

#include "../interpolation/InterpolationEngine.h"
#include "../shape/Point3D.h"
#include "../util/GraphicsConversionUtility.h"


namespace XOR {

/**
 * Positionable is an abstract parent class for objects that need to have
 * accurate positioning in 3D space. This class is a conglomeration of the old
 * Positionable and Orientate classes. It provides three-way rotation,
 * translation, and interpolation (activated by providing an
 * InterpolationEngine to any of the methods below).
 *
 * For efficiency reasons, Positionable is a declared as a friend class in both
 * Translate and Rotate
 *
 * I hate default parameters, which is why there are overloaded mutation methods.
 * 
 * @author John Magnotti, Michael Lam
 * @version 1.0
 */
class Positionable : public Transform
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
	Positionable();


	/**
	 * Destructor
	 */
	virtual ~Positionable();


    /**
     * Copies the values from the other Positionable, no aliasing
     */
    void clone(Positionable *);

    
    /**
     * returns a clone of the translation
     */
    Dimension3D * getTranslation();


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
    void setTranslation(Dimension3D * position);
    void setTranslation(Dimension3D * position, InterpolationEngine * interpolation);
            


    /**
     * Increments the translation for the object. 
     * This is the a concatenation routine.
     *
     * @param position      A translate object that represents the new position
     *                      of the object.
     * @param interpolation An interapolation engine to be used to interpolate
     *                      the model change
     */
    void incrementTranslation(Dimension3D * position);
    void incrementTranslation(Dimension3D * position, InterpolationEngine * interpolation);


	/**
	 * Get the current value of a rotation
	 * Dimensions: 0=theta,1=phi, 2=roll;
	 */
	float getRotation(int dimension);


    /**
     * Sets the rotation for the given axis. axis must be one of 
     * Positionable::THETA, Positionable::PHI, or Positionable::ROLL. 
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
     * Positionable::THETA, Positionable::PHI, or Positionable::ROLL.
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
     * Returns the scalar
     */
    float getScalar();


    /**
     * Sets the scale transformation. Note that this, like other transforms,
     * does not modify the actual parameters. 
     * This is NOT a concatenation routine.
     *
     * @param scalar        A dimension3D object with scalar values.
     * @param interpolation An interapolation engine to be used to interpolate
     *                      the model change.
     */
    void setScalar(Dimension3D * scalar);
    void setScalar(Dimension3D * scalar, InterpolationEngine * interpolation);


    /**
     * Increments the scalar value.
     * This is the concatenation routine.
     *
     * @param scalar        A dimension3D object with scalar values.
     * @param interpolation An interapolation engine to be used to interpolate
     *                      the model change.
     */
    void incrementScalar(Dimension3D * scalar);
    void incrementScalar(Dimension3D * scalar, InterpolationEngine * interpolation);


    /**
     * Returns the state of the transformed variable, which is set to TRUE when
     * 
     * @return Whether or not the object has been transformed.
     */
    bool isTransformed();


    /**
     * Used to support primitive Reflection.
     *
     * @return A string representing the type of the renderable (i.e.
     *         "POSITIONABLE").
     */
    virtual char * getRenderableType();


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
	 * Get a clone of the local focal point
	 */
	Dimension3D * getFocalPoint();


	/**
	 * Easy way to set the focus point.
	 * Automatically adjusts rotations to match given point.
	 */
    void setFocalPoint(Dimension3D * point);
    void setFocalPoint(Dimension3D * point, InterpolationEngine * interpolable);


    void incrementFocalPoint(Dimension3D * point);
    void incrementFocalPoint(Dimension3D * point, InterpolationEngine * interpolable);


	/**
	 * Easy way to move the camera a certain distance
	 * along its focus vector.
	 */
	void walk(float distance, InterpolationEngine * interpolation);


	/**
	 * Print all member info for debug purposes.
	 */
	void printDebugInfo();
	
    /**
     * remove the effect of all of the transform objects
     */
    void clear();

protected:
    
	Rotate * _phi;
	Rotate * _roll;
	Rotate * _theta;
	
    Scale * _scale;

	Translate * _position;
	Translate * _focalPoint;

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

#endif			// POSITIONABLE_H


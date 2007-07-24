#ifndef TRANSLATE_H
#define TRANSLATE_H


#include <iostream>
#include <vector>
#include <stdio.h>

#include "Transform.h"

#include "../geometry/Vector3D.h"
#include "../geometry/Vector2D.h"
#include "../geometry/Dimension2D.h"
#include "../geometry/Dimension3D.h"
#include "../event/timer/Timer.h"
#include "../event/Action.h"
#include "../interpolation/InterpolatorFactory.h"
#include "../interpolation/Interpolator.h"


using namespace std;

namespace XOR {


/**
 * Allows for translation of an object. This is accomplished through
 * manipulation of the GL Matrix Stack.
 *
 * @author John Magnotti
 * @author Michael Lam
 * @version 1.1
 */
class Translate : public Transform
{

public:

	/*
	 * Destructor
	 */
	virtual ~Translate();


	/**
	 * Explicit Constructors for immediate translations
	 */
	static Translate * CreateTranslate(float x, float y, float z);
	static Translate * CreateTranslate(Vector3D * position);


	/**
	 * Explicit Constructors for interpolated translations
	 */
	static Translate * CreateTranslate(float x, float y, float z, int milliseconds);
	static Translate * CreateTranslate(float x, float y, float z, int milliseconds, Action * action);

    /**
     * @param position The ending position for the translation -- this value is
     * aliased. Memory will be released when this Translate is deleted. 
     */
	static Translate * CreateTranslate(Vector3D * position, int milliseconds);
    
    /**
     * 
     * @param position The ending position for the translation -- this value is
     * aliased. Memory will be released when this Translate is deleted. 
     */
	static Translate * CreateTranslate(Vector3D * position, int milliseconds, Action * action);


    /**
     * Copies the value of the other Translate, no aliasing 
     */
    void clone(Translate * other);


	/**
	 * Applies the translation
	 */
	virtual void push(void);


	/**
	 * Applies the reverse translation, -1 * [X, Y, Z]
	 */
	virtual void pushInverse(void);

	
	/**
	 * Direct access to the translate member.
	 * Calling class is responsible for deleting the memory associated with position.
	 */
	void setTranslation(Vector3D * position);
	

	/**
	 * Returns the translation as a Vector3D
     *
     * @returns A new vector representing the Translate object. The memory
     * associated with this Vector3D must be freed by the caller.
	 */
	Vector3D * toVector();


    void print();

    /**
     * Clears out the transform. Pushing this transform will no longer modify
     * the stack in a meaningful way.
     */
    void toIdentity();

	void transform(Vector3D * position);
	void transform(Dimension3D * size);

	void transform(Vector2D * position);
	void transform(Dimension2D * size);

protected:

    // is this still needed? 07/07
    friend class Orientation;
	
	float _translation [3];
    Translate(float x, float y, float z);
    Translate(Vector3D * position);

};

class InterpolatedTranslate : public Translate
{

public:

    InterpolatedTranslate(float x, float y, float z, int milliseconds);
    InterpolatedTranslate(float x, float y, float z, int milliseconds, Action * action);

    InterpolatedTranslate(Vector3D * position, int milliseconds);
	InterpolatedTranslate(Vector3D * position, int milliseconds, Action * action);

    // advances the interpolation if necessary
	void push();

    // advances the interpolation if necessary
	void pushInverse();

    /**
     * incremements the interpolated values
     */
    void interpolate();

    void build(Vector3D * position, int milliseconds, Action * action);


private:

	vector<Vector3D*> * _steps;

	Vector3D * _target;

	int _remaining, _total;
    Action * _action;
};

class ImmediateTranslate : public Translate
{

public:


    ImmediateTranslate(Vector3D * position);

    ImmediateTranslate(float x, float y, float z); 

};

}

#endif			// TRANSLATE_H


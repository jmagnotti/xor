#ifndef TRANSLATE_H
#define TRANSLATE_H


#include <iostream>
#include <stdio.h>

#include "Transform.h"
#include "../geometry/Vector3D.h"
#include "../geometry/Vector2D.h"
#include "../geometry/Dimension2D.h"
#include "../event/timer/TimerListener.h"


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
	//static Translate * CreateTranslate(float x, float y, float z, int milliseconds, InterpolationAction * action);

	static Translate * CreateTranslate(Vector3D * position, int milliseconds);
	//static Translate * CreateTranslate(Vector3D * position, int milliseconds, InterpolationAction * action);


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
	 * Returns the translation as a vector
	 */
	Vector3D * toVector();


    void print();

    void toIdentity();

	void transform(Vector3D * position);
	void transform(Dimension3D * size);

	void transform(Vector2D * position);
	void transform(Dimension2D * size);

	// Is there a point to this? -ML
    //Translate * createTransformedInstance(Vector3D * point);
    //Translate * createTransformedInstance(Vector3D * point, int milliseconds);

protected:

    friend class Orientation;
	
	float _translation [3];
    Translate(float x, float y, float z);
    Translate(Vector3D * position);

};

class InterpolatedTranslate : public Translate
{

public:

    InterpolatedTranslate(float x, float y, float z, int milliseconds);
    //InterpolatedTranslate(float x, float y, float z, int milliseconds, InterpolationAction * action);

    InterpolatedTranslate(Vector3D * position, int milliseconds);
    //InterpolatedTranslate(Vector3D * position, int milliseconds, InterpolationAction * action);

    // advances the interpolation if necessary
	void push();

    // advances the interpolation if necessary
	void pushInverse();

private:


	// _step should be a collection
	Vector3D * _step, * _target;

	int _remaining;
};

class ImmediateTranslate  : public Translate
{

public:


    ImmediateTranslate(Vector3D * position);

    ImmediateTranslate(float x, float y, float z); 

};

}

#endif			// TRANSLATE_H


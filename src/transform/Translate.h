#ifndef TRANSLATE_H
#define TRANSLATE_H


#include <iostream>
#include <vector>

#include "Transform.h"
#include "../interpolation/InterpolationEngine.h"
#include "../geometry/Vector3D.h"


using namespace std;

namespace XOR {


/**
 * Applies a translate transform
 */
class Translate : public Transform
{
	friend class Transformable;

public:

	/*
	 * Creates an Identity Translation.
	 */
	Translate();


	/**
	 * Explicit Constructor
	 */
	Translate(float, float, float);


	/**
	 * Explicit Constructor
	 */
	Translate(Vector3D *);


    /**
     * Copies the value of the other translates, no aliasing 
     */
    void clone(Translate *);


	/**
	 * Applies the translation
	 */
	void push(void);


	/**
	 * Applies the reverse translation
	 */
	void pushInverse(void);


    /*
     * resets the translation to have no effect
     */
    void clear();
	

	/**
	 * Easy way to increment a translation
	 * to decrement, just increment by a negative amount
	 */
    void increment(Vector3D *, InterpolationEngine * interpolation=NULL);
    void set(Vector3D *, InterpolationEngine * interpolation=NULL);

	Vector3D * toVector();

private:
	
	float _xShift, _yShift, _zShift;

    vector<float*> _values;
    vector<float> _out;

};

}

#endif			// TRANSLATE_H


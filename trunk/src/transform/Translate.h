#ifndef TRANSLATE_H
#define TRANSLATE_H


#include <iostream>

#include "Transform.h"
#include "../geometry/Dimension3D.h"


using namespace std;

namespace XOR {


/**
 * Applies a translate transform
 */
class Translate : public Transform
{
	friend class Positionable;

public:

	/**
	 * Explicit Constructor
	 */
	Translate(float, float, float);


	/**
	 * Explicit Constructor
	 */
	Translate(Dimension3D *);


	/**
	 * Static Constructor for your convenience
	 */
	static Translate * CreateTranslation(float x, float y, float z);
    

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
	

	/**
	 * Easy way to increment a translation
	 * to decrement, just increment by a negative amount
	 */
	void increment(Dimension3D*);


    /**
     * Interpolable mehtods.
     */
    void scale(Interpolable *other, int numSteps);
    void next(void);


protected:
	
	float _xShift, _yShift, _zShift;

    list<float*> * _values;

};

}

#endif			// TRANSLATE_H


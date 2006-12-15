#ifndef TRANSLATE_H
#define TRANSLATE_H


#include <iostream>

#include "Transform.h"
#include "../shape/Point3D.h"


using namespace std;

namespace XOR {


/**
 * Applies a translate transform
 */
class Translate : public Transform
{
	friend class Orientate;

public:

	/**
	 * Explicit Constructor
	 */
	Translate(float, float, float);


	/**
	 * Explicit Constructor
	 */
	Translate(Point3D *);


	/**
	 * Static Constructor for your convenience
	 */
	static Translate * CreateTranslation(float, float, float);
    

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
	void increment(Point3D*);


protected:
	
	float		_xShift, _yShift, _zShift;

};

}

#endif			// TRANSLATE_H


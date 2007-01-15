#ifndef TRANSLATE_H
#define TRANSLATE_H


#include <iostream>
#include <vector>

#include "Transform.h"
#include "../interpolation/InterpolationEngine.h"
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


    /*
     * resets the translation to have no effect
     */
    void clear();
	

	/**
	 * Easy way to increment a translation
	 * to decrement, just increment by a negative amount
	 */
    void increment(Dimension3D *, InterpolationEngine * interpolation=NULL);
    void set(Dimension3D *, InterpolationEngine * interpolation=NULL);


protected:
	
	float _xShift, _yShift, _zShift;
    vector<float*> _values;
    vector<float> _out;

};

}

#endif			// TRANSLATE_H


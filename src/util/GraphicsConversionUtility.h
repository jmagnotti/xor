#ifndef GRAPHICSCONVERSIONUTILITY_H
#define GRAPHICSCONVERSIONUTILITY_H

#include <math.h>

#include "../../include/SDL_opengl.h"
#include "../geometry/Vector3D.h"


using namespace std;

namespace XOR {

/**
 * For now this is kind of a catch-all for applying transformations to "graphics," or calculations
 * somehow related to graphics.
 * The word "utility" in the class name is my way of rationalizing the intended clutter.
 *
 * This started as a place to put the mapValue function. Hopefully it will gain
 * more structure at some point.
 */
class GraphicsConversionUtility
{

public:

    static const float PI;

    /**
     * Singleton accessor method
     */
	static GraphicsConversionUtility * GetInstance(void);


	/**
	 * Returns the cross product [vecA-vecB] x [vecB - vecC] 
	 */
	Vector3D * crossProduct(Vector3D * vecA, Vector3D * vecB, Vector3D * vecC);
	

	/**
	 * Converts the given float degree in to radians RAD*PI/180
	 */
    inline float degressToRadians(float degree);

	
	/** 
	 * Compares two float values for equality, uses the specified epsilon value
	 * or default of 0.1
	 */
	bool compare_f(float, float, float epsilon = 0.01);


	/**
	 * Converts a given ratio value to a ratio value in another system. I think
	 * ratio value is the right phrase.
	 */
	float mapValue(float value, float min, float max, float targetmin, float targetmax);


	/**
	 * Calls sqrtf, so it is kind of slow, and should only be done once
	 * for a given surface.
	 */
	void normalize(Vector3D * points[6]);


    /**
     * Performs c = a % b
     */
    float floatModulus(float a, int b);


private:

	GraphicsConversionUtility();

	static GraphicsConversionUtility * _graphicsConversionUtility;
	
};

}

#endif			// GRAPHICSCONVERSIONUTILITY_H


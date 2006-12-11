#ifndef GRAPHICSCONUTIL_H
#define GRAPHICSCONUTIL_H


#include <math.h>
#include <map>

#include "../shape/Point3D.h"


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
	Point3D * crossProduct(Point3D * vecA, Point3D * vecB, Point3D * vecC);
	

	/**
	 * converts the given float degree in to radians RAD*PI/180
	 * calling this too often (1mill+) will slow you down, just do the conversion
	 * inline
	 */
    inline float degressToRadians(float degree);


	/**
	 * Accessor to the cosine table, only holds values for every 5 deg
	 * Mods by 360 to handle large numbers
	 */
	float getCosine(int deg);


	/**
	 * Accessor to the sine table, only holds values for every 5 deg
	 * Mods by 360 to handle large numbers
	 */
	float getSine(int deg);

	
	/** 
	 * Compares two float values for equality, uses the specified epsilon value
	 * or default of 0.1
	 */
	bool compare_f(float, float, float epsilon = 0.01);


	/**
	 * Converts a given ratio value to a ratio value in another system. I think
	 * ratio value is the right phrase.
	 * --The crux of this method is credited to joshblake@gmail.com
	 */
	inline float mapValue(float value, float min, float max, float targetmin, float targetmax);


	/**
	 * Calls sqrtf, so it is kind of slow, and should only be done once
	 * for a given surface.
	 */
	void normalize(Point3D * points[6]);


protected:
	GraphicsConversionUtility(void);

private:

	static GraphicsConversionUtility * _graphicsConversionUtility;
	
	/**
	 * store commonly used values in hashtables for 
	 * fast and efficient usage
	 */
	map<int, float>cosineValues;
	map<int, float>sineValues;

};

}

#endif			//GRAPHICSCONUTIL_H


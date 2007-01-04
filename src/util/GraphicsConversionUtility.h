#ifndef GRAPHICSCONUTIL_H
#define GRAPHICSCONUTIL_H


#include <math.h>
#include <map>

#include "../../include/SDL_opengl.h"

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
	 * Converts the given float degree in to radians RAD*PI/180
	 */
    inline float degressToRadians(float degree);


    /**
     * Just a pass through
     */
	float getCosine(int deg);


	/**
     * Just a pass through
	 */
	float getSine(int deg);


    /**
     * Compiles the object (and all subobjects) to OpenGL display lists. This
     * should be called after object creation but before initial rendering.
     * Note that this does go through the render method, but nothing is drawn
     * to the screen.
     */
    void generateDisplayList(GLuint & displayListID, Renderable * renderable); 

	
	/** 
	 * Compares two float values for equality, uses the specified epsilon value
	 * or default of 0.1
	 */
	bool compare_f(float, float, float epsilon = 0.01);


	/**
	 * Converts a given ratio value to a ratio value in another system. I think
	 * ratio value is the right phrase.
	 */
	inline float mapValue(float value, float min, float max, float targetmin, float targetmax);


	/**
	 * Calls sqrtf, so it is kind of slow, and should only be done once
	 * for a given surface.
	 */
	void normalize(Point3D * points[6]);

    /**
     * Performs c = a % b
     */
    float floatModulus(float a, int b);


protected:
	GraphicsConversionUtility(void);

private:

	static GraphicsConversionUtility * _graphicsConversionUtility;
	
	/**
	 * store commonly used values in hashtables for 
	 * fast and efficient usage
     * This may not be fast or efficient. Test this.
	 */
    //	map<int, float>cosineValues;
    //	map<int, float>sineValues;

};

}

#endif			//GRAPHICSCONUTIL_H


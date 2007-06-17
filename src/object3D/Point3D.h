#ifndef POINT3D_H
#define POINT3D_H


#include <iostream>
#include <string>
#include <math.h>

#include <SDL/SDL_opengl.h>

#include "../paint/Paint.h"
#include "../geometry/Vector3D.h"

#include "Object3D.h"

using namespace std;

namespace XOR {

/**
 * Should be a Point class that point3D extends.
 * Represents a point in 3D space.
 */
class Point3D
{

public:


    /**
     * Destructor
     */
    virtual ~Point3D();


	/**
	 * Explicit Constructor
	 * 
	 * Construct a point at x,y,z
	 */
	Point3D(float x, float y, float z);


    /**
	 * Explicit Constructor
	 * 
	 * Create a point from the float array
	 */
	Point3D(float p[3]);


	/**
	 * Explicit Constructor
	 * 
	 * Create a point from the float array
	 */
	Point3D(Vector3D * position);


	/**
	 * Explicit Constructor
	 * 
	 * Create a point3D from 3 position values and 3 color values (RGB)
	 */
	Point3D(float p[3], float c[3]);


	/**
	 * Explicit Constructor
	 *
	 * Creates a point from the given positions and using the specified color
	 */
	Point3D(float x, float y, float z, float c[3]);


	/**
	 * Explicit Constructor
	 * This constructor is to be used only by the XML-to-GOR Tool. 
	 * Use the other constructors for other uses, as they are MUCH more efficeint
	 */
//	Point3D * CreatePoint3D(String, String, String);


	/**
	 * Adds the float[3] to the point
	 */
	void increment(float[3]);


    /**
     * Copies the values from the points position to this one
     */
    void clonePosition(Point3D * p);


    /**
	 * This is a really important method that should be used more often. Any 
     * time you need the exact opposite of this point, call this function. 
	 */
	Point3D * invert();


    /**
	 * Sets the color, then renders the point.
	 * No delegation occurs at this level, only a glColor and a glVertex are used.
	 */
	void render(void);


    char * toString();


    Vector3D * getPosition();

	/**
	 * Returns the specified position, or 0 if position > 3 || position < 0
	 */
    float get(int position);

	/**
	 * Returns a float representation of the color
	 */
    float * getColor();


    //--- SETTERS ---//
	void setColor(float c[3]);
    void setColor(Paint * paint);
    void setPosition(float position[3]);
    void setPosition(Vector3D * position);

private:

	Point3D();
	Vector3D * _position;
	float * _color;
    
};

}

#endif			// POINT3D_H


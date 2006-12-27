#ifndef POINT3D_H
#define POINT3D_H


#include <iostream>

#include <string>
#include <math.h>

#include "../paint/Paint.h"
#include "Renderable.h"
#include "../../include/SDL_opengl.h"

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
	 * Default Constructor
	 * 
	 * Construct a point at 0,0,0, colored white
	 */
	Point3D();


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
     * Required by Interpolable.h.
     * Returns if the given points position matches this points position
     */
    //bool compare(Interpolable * interp);


    /**
	 * This is a really important method that should be used more often. Any 
     * time you need the exact opposite of this point, call this function. 
     * Quadrilateral3D::setNormal(Point3D*) is an example of using invert, 
     * as well as some of the collision detection routines.
	 */
	Point3D * invert();


    /**
     * Finds the min and max of the two points and stores the minimum values in a, and the maximum
     * values in b. Retains respective color values.
     */
//    void minAndMax(Point3D * a, Point3D * b);


    /**
     * Required by Interpolable.h.
     * Increments the position of the point according to the values of the 
     * given interpolable.
     */
    //void next(Interpolable * interp);
    
    
    /**
	 * Sets the color, then renders the point.
	 * No delegation occurs at this level, only a glColor and a glVertex are used.
	 */
	void render(void);


    /*
     * Required by Interpolable.h.
     * Returns a point that represents one step of "steps" sections between the 
     * two given points.
     */
    //Interpolable * scale(Interpolable * begin, Interpolable * finsh, int steps);

    
    /**
	 * Multiplies each point by the specified value
	 */
//	void scale(float);


    /**
     * Required by Interpolable.h
     */
    //void set(Interpolable * interp);


	/**
	 * Adds the two points and returns a new
	 * point
	 */
	Point3D * operator +(Point3D * point);


	/**
	 * Subtracts the two points and returns a new
	 * point
	 */
	Point3D * operator -(Point3D * point);


    char * toString();


	//--- GETTERS ---//
    float   get(int);
    float	getX();
	float	getY();
	float	getZ();

    float * getPosition();
    float * getColor();


    //--- SETTERS ---//
	void setColor(float c[3]);
    void setColor(Paint*);
    void setPosition(float pos[3]);

protected:

	float * _position;
    //Translate * _position;
 
	float * _color;
    
};

}

#endif			// POINT3D_H


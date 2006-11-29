#ifndef CUBE_H
#define CUBE_H


#include "../paint/Paint.h"
#include "Point3D.h"
#include "RectangularPrism.h"


namespace XOR {


/**
 * A simpler form of a rectangular prism. Namely, one with equilateral sides.
 */
class Cube : public RectangularPrism
{

public:

	/**
	 * Default Constructor.
	 * Creates a cube with front bottom left at origin with a size of 1
	 */
  	Cube();


	/**
	 * Explicit Constructor.
	 * Create a cube with the given registration point, radius, and Paint object
	 */
	Cube(Point3D*, float, Paint*);


	/**
	 * Explicit Constructor.
	 * This constructor is to be used only by the XML-to-GOR Tool. 
	 * Use the other constructors for other uses, as they are MUCH more efficeint
	 */
//	static Cube * CreateCube(String, String, String, String);

};

}

#endif			// CUBE_H


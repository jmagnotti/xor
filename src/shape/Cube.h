#ifndef CUBE_H
#define CUBE_H


#include "../paint/Paint.h"
#include "Point3D.h"
#include "RectangularPrism.h"


namespace XOR {


/**
 * A simpler form of a rectangular prism. Namely, one with equilateral sides.
 *
 * @author John Magnotti, Michael Lam
 * @version 1.0
 */
class Cube : public RectangularPrism
{

public:

	/**
     * Creates a cube with front bottom left at origin with a size of 1
	 */
  	Cube();


	/**
     * Create a cube with the given registration point, radius, and Paint
     * object
     * 
     * @param point Front bottom left corner of the Cube
     * @param size  Size for each dimension of the Cube
     * @param paint Paint object for painting the Cube
	 */
	Cube(Point3D * point, float size, Paint * paint);


	/**
	 * Explicit Constructor.
	 * This constructor is to be used only by the XML-to-GOR Tool. 
     * Use the other constructors for other uses, as they are MUCH more
     * efficeint
	 */
//	static Cube * CreateCube(String, String, String, String);

};

}

#endif			// CUBE_H


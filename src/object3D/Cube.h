#ifndef CUBE_H
#define CUBE_H


#include "../paint/Paint.h"
#include "../geometry/Vector3D.h"
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
     * Create a cube with the given registration point, radius, and Paint
     * object
     * 
     * @param point Front bottom left corner of the Cube
     * @param size  Size for each dimension of the Cube
     * @param paint Paint object for painting the Cube
	 */
	Cube(Vector3D * point, float size, Paint * paint);


	/**
	 * Explicit Constructor.
	 * This constructor is to be used only by the XML-to-XOR (XXOR) Tool. 
     * Use the other constructors for other uses, as they are MUCH more
     * efficient.
	 */
//	static Cube * CreateCube(String, String, String, String);

private:

	Cube();

};

}

#endif			// CUBE_H


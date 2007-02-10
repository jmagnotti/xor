#include "Cube.h"

namespace XOR {

/* 
 * Explicit Constructor
 */
Cube::Cube(Vector3D * point, float size, Paint * paint) :
	RectangularPrism(point, size, size, size, paint)
{}

}


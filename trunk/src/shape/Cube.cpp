#include "Cube.h"

namespace XOR {

/*
 * Default Constructor
 */
Cube::Cube()
{
	_paint = new Paint(Color::WHITE, Paint::HEIGHT_BASED);
	_volume = new RectangularVolume();
	setup();
}


/* 
 * Explicit Constructor
 */
Cube::Cube(Point3D * point, float size, Paint * p)
{
	_paint = p;
	_volume = new RectangularVolume(point, size);
	setup();	
}

}


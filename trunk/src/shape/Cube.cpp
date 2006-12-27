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
Cube::Cube(Point3D * point, float size, Paint * paint)
{
    /*
     * Why are paint constants messing up?
     *
        float * c = p->getColorFrom();
        float * d = p->getColorTo();

        std::cout << "FROM: " << c[0] << " " << c[1] << " " << c[2] << endl; 
        std::cout << "TO: " << d[0] << " " << d[1] << " " << d[2] << endl; 
    */

	_paint = paint;
	_volume = new RectangularVolume(point, size);
	setup();	
}

}


#include "Square3D.h"


namespace XOR {

/*
 * Default Constructor
 */
Square3D::Square3D()
{
    _paint = new Paint(Color::WHITE);

	_vertices[0] = new Point3D(0.0f, 0.0f, 0.0f);
	_vertices[1] = new Point3D(0.0f, 1.0f, 0.0f);
	_vertices[2] = new Point3D(1.0f, 1.0f, 0.0f);
	_vertices[3] = new Point3D(1.0f, 0.0f, 0.0f);
}

/*
 * Explicit Constructor
 */
Square3D::Square3D(Point3D * point, float diameter, Paint * paint)
{
    _paint = paint;

	_vertices[0] = point; 
	_vertices[1] = new Point3D(point->getX()+diameter, point->getY(), point->getZ());
	_vertices[2] = new Point3D(point->getX()+diameter, point->getY()+diameter, point->getZ());
	_vertices[3] = new Point3D(point->getX(), point->getY()+diameter, point->getZ());

    setAllColors(_paint);
}

}


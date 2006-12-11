#include "Square3D.h"


namespace XOR {

/*
 * Default Constructor
 */
Square3D::Square3D()
{
	Quadrilateral3D::Quadrilateral3D();
}

/*
 * Explicit Constructor
 */
Square3D::Square3D(Point3D * point, float diameter, Paint * paint)
{
	Quadrilateral3D(point, 
			new Point3D(point->getX()+diameter, point->getY(), point->getZ()),
			new Point3D(point->getX()+diameter, point->getY()+diameter, point->getZ()),
			new Point3D(point->getX(), point->getY()+diameter, point->getZ()),
			   	paint);

}

}


#include "RectangularVolume.h"


namespace XOR {

/*
 * Default Constructor
 */
RectangularVolume::RectangularVolume()
{
	_origin = new Vector3D(0.0f, 0.0f, 0.0f);
	_radii = new Dimension3D(1.0f);
}

/*
 * Explicit Constructor.
 * This is the preferred method of creation, as it directly mimics the
 * structure of the rectvol.
 */
RectangularVolume::RectangularVolume(Vector3D * point, Dimension3D * size)
{
	_origin = point;
	_radii  = size;

	// let's do some tricks that will make collision detection easier: if
	// they give us a negative dimension, invert the necessary parts of the point of origin so we
	// can make them all nonnegative.
	for(int i=0; i<3; i++) {
		if (_radii->get(i) < 0) {
			// push the origin to the edge 
			_origin->setPosition(i, _origin->get(i) + _radii->get(i));

			// flip the dimension so the bounding region is the same 
			_radii->set(i, -1 * _radii->get(i));
		}
	}
}

/*
 * Explicit Constructor
 * Create a volume based on the bottom left coord and width, 
 * length, and height
 */
RectangularVolume::RectangularVolume(float lowerX,	float lowerY, float lowerZ,
									 float width,	float height, float depth)
{
	_origin = new Vector3D(lowerX, lowerY, lowerZ);
	_radii = new Dimension3D(width, height, depth);
}


/*
 * Explicit Constructor
 * Easy cube constructor
 */
RectangularVolume::RectangularVolume(Vector3D * corner, float radius)
{
	_origin = corner;
	_radii = new Dimension3D(radius);		
}


/*
 * Tests if the given point is contained (intersected) by the 
 * rectangular volume object
 */
bool RectangularVolume::contains(Vector3D * point)
{
	bool contains = false;

	// check each type of collision, only contained if contained by all 3
	if (	(!(		point->getX() < _origin->getX()  
				||  point->getX() > _origin->getX() + getXDiameter() )) && 
			(!(		point->getZ() < _origin->getZ()
				||  point->getZ() > _origin->getZ() + getZDiameter()) ) &&
			(!(		point->getY() < _origin->getY()
				||  point->getY() > _origin->getY() + getYDiameter()) )	)
	{
		 contains = true;
	}

	return contains;
}

bool RectangularVolume::contains(Containment * container, Vector3D * point)
{
    if (point->getX() < _origin->getX() ||  
        point->getX() > _origin->getX() + getXDiameter() ) 
        container->setXContained(false);
    else
        container->setXContained(true);

    if (point->getY() < _origin->getY() ||
        point->getY() > _origin->getY() + getYDiameter())
        container->setYContained(false);
    else
        container->setYContained(true);

    if (point->getZ() < _origin->getZ() ||  
        point->getZ() > _origin->getZ() + getZDiameter())
        container->setZContained(false);
    else
        container->setZContained(true);

//    container->print();
    
    return container->isFullyContained();
}


/*
 * generate the bounding points of the volume
 */
void RectangularVolume::generatePoints(Vector3D * points[8])
{
	//low Y points
	points[0] = new Vector3D(_origin->getX(), _origin->getY(),
							 _origin->getZ());				

	points[1] = new Vector3D(_origin->getX(), _origin->getY(), _origin->getZ()
							 + getZDiameter() );

	points[2] = new Vector3D(_origin->getX() + getXDiameter(), _origin->getY(),
							 _origin->getZ() + getZDiameter() );
	
	points[3] = new Vector3D(_origin->getX() + getXDiameter(),
							 _origin->getY(), _origin->getZ() );

	//high Y points
	points[4] = new Vector3D(_origin->getX(), _origin->getY() + getYDiameter(),
							 _origin->getZ() );

	points[5] = new Vector3D(_origin->getX(), _origin->getY() + getYDiameter(),
							 _origin->getZ() + getZDiameter() );

	points[6] = new Vector3D(_origin->getX() + getXDiameter(), _origin->getY()
							 + getYDiameter(), _origin->getZ() + getZDiameter() );

	points[7] = new Vector3D(_origin->getX() + getXDiameter(), _origin->getY()
							 + getYDiameter(), _origin->getZ() );
}


/*
 * dimension clone
 */
Dimension3D * RectangularVolume::getDimension()
{
	return new Dimension3D(getXDiameter(), getYDiameter(), getZDiameter());
}

//--getters for diameters--//
float RectangularVolume::getXDiameter()
{
	return _radii->getWidth();
}

float RectangularVolume::getYDiameter() 
{	
	return _radii->getHeight();
}

float RectangularVolume::getZDiameter()
{
	return _radii->getDepth();	
}

Vector3D * RectangularVolume::getOrigin() 
{
	return _origin;
} 

}


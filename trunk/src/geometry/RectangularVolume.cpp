#include "RectangularVolume.h"


namespace XOR {

/*
 * Default Constructor
 */
RectangularVolume::RectangularVolume()
{
	frontBottomLeftCorner = new Point3D(0.0f, 0.0f, 0.0f);
	_radii = new Dimension3D(1.0f);
}


/*
 * Explicit Constructor.
 * This is the preferred method of creation, as it directly mimics the structure of the rectvol.
 */
RectangularVolume::RectangularVolume(Point3D * point, Dimension3D * size)
{
	frontBottomLeftCorner = point;
	_radii = size;

}


/*
 * Explicit Constructor
 * Create a volume based on the bottom left coord and width, 
 * length, and height
 */
RectangularVolume::RectangularVolume(	float lowerX,	float lowerY, float lowerZ,
										float width,	float height, float depth)
{
	frontBottomLeftCorner = new Point3D(lowerX, lowerY, lowerZ);
	_radii = new Dimension3D(width, height, depth);
}


/*
 * Explicit Constructor
 * Easy cube constructor
 */
RectangularVolume::RectangularVolume(Point3D * corner, float radius)
{
	frontBottomLeftCorner = corner;
	_radii = new Dimension3D(radius);		
}


/*
 * Tests if the given point is contained (intersected) by the 
 * rectangular volume object
 */
bool RectangularVolume::contains(Point3D * p)
{
	bool contains = false;


	// check each type of collision, only collides if contained by all 3
	if (	(!(		p->getX() < frontBottomLeftCorner->getX()  
				||  p->getX() > frontBottomLeftCorner->getX() + getXDiameter() )) && 
			(!(		p->getZ() < frontBottomLeftCorner->getZ()
				||  p->getZ() > frontBottomLeftCorner->getZ() + getZDiameter()) ) )
				
			//	&&
			//(!(		p->getY() < frontBottomLeftCorner->getY()
			//	||  p->getY() > frontBottomLeftCorner->getY() + radii[1]) )		)
	{
		 contains = true;
	}

	return contains;
}


/*
 * generate the bounding points of the volume
 */
void RectangularVolume::generatePoints(Point3D * points[8])
{
	//low Y points
	points[0] = new Point3D(frontBottomLeftCorner->getX(),
			 				frontBottomLeftCorner->getY(),
							frontBottomLeftCorner->getZ() );				

	points[1] = new Point3D(frontBottomLeftCorner->getX(),
							frontBottomLeftCorner->getY(),
							frontBottomLeftCorner->getZ() + getZDiameter() );

	points[2] = new Point3D(frontBottomLeftCorner->getX() + getXDiameter(),
							frontBottomLeftCorner->getY(),
							frontBottomLeftCorner->getZ() + getZDiameter() );
	
	points[3] = new Point3D(frontBottomLeftCorner->getX() + getXDiameter(),		
							frontBottomLeftCorner->getY(),
							frontBottomLeftCorner->getZ() );

	//high Y points
	points[4] = new Point3D(frontBottomLeftCorner->getX(),
							frontBottomLeftCorner->getY() + getYDiameter(),
							frontBottomLeftCorner->getZ() );

	points[5] = new Point3D(frontBottomLeftCorner->getX(),
							frontBottomLeftCorner->getY() + getYDiameter(),
							frontBottomLeftCorner->getZ() + getZDiameter() );

	points[6] = new Point3D(frontBottomLeftCorner->getX() + getXDiameter(),
							frontBottomLeftCorner->getY() + getYDiameter(),
							frontBottomLeftCorner->getZ() + getZDiameter() );

	points[7] = new Point3D(frontBottomLeftCorner->getX() + getXDiameter(),
							frontBottomLeftCorner->getY() + getYDiameter(),
							frontBottomLeftCorner->getZ() );

/*
    cout << "Generated Points: " << endl;
    for (int i=0; i<8; i++)
        cout << "\t" << i << ": " << points[i]->toString() << endl;
    cout << "__" << endl;
*/

}


//--GETTERS FOR DIAMETERS--//
float RectangularVolume::getXDiameter() {	return _radii->getWidth();	}
float RectangularVolume::getYDiameter() {	return _radii->getHeight();	}
float RectangularVolume::getZDiameter() {	return _radii->getDepth();	}

Point3D * RectangularVolume::getRegistrationPoint() {	return frontBottomLeftCorner; }

}


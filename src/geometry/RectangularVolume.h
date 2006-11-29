#ifndef RECTANGULARVOLUME_H
#define RECTANGULARVOLUME_H


#include "Dimension3D.h"
#include "../shape/Point3D.h"


namespace XOR {

/**
 * Encapsulates the volume of an object. Contains information about _radii 
 * in three directions and the front bottom left corner of an object
 * the main purpose of this object is collision detection, and is meant to be contained 
 * by a rectangularprism if painting is required. NOTE: RectangularVolume is NOT a Renderable.
 * 
 * Also, allows a rectangularprism to switch out its volumes, or for multiple 
 * RectangularPrisms to share the same volume. Then, just use glTranslate to move their
 * position. Consider this implementation for the maze program, using display lists once the 
 * cubes are generated. HOWEVER, the idea is to move away from the state machine. Using glTranslate is a 
 * move in the wrong direction.
 */
class RectangularVolume
{

public:

	/**
	 * Default Constructor
	 */
	RectangularVolume();


	/**
	 * Explicit Constructor.
	 * This is the preferred method of creation, as it directly mimics the structure of the rectvol.
	 */
	RectangularVolume(Point3D * point, Dimension3D * size);


	/**
	 * Explicit Constructor
	 * Create a volume based on the bottom left coord and width, 
	 * length, and height
	 */
	RectangularVolume(	float lowerX,	float lowerY, float lowerZ,
						float width,	float height, float depth);


	/**
	 * Explicit Constructor
	 * Easy cube constructor
	 */
	RectangularVolume(Point3D * corner, float radius);


	/**
	 * Tests if the given point is contained (intersected) by the 
	 * rectangular volume object
	 */
	bool contains(Point3D * p);


	/**
	 * Checks for containment within a specified plane.
	 * The idea is that this is faster than checking all planes
	 * each time
	 */
	bool contains(Point3D * p, int plane);
	

	/**
	 * Generates a set of points that uniquely define the given volume
	 */
	void generatePoints(Point3D * points[8]);


	//--GETTERS FOR DIAMETERS--//
	float getXDiameter();
	float getYDiameter();
	float getZDiameter();

	Point3D * getRegistrationPoint();


protected:

	Dimension3D * _radii;
	Point3D		* frontBottomLeftCorner;


};

}

#endif			// RECTANGULARVOLUME_H


#ifndef RECTANGULARVOLUME_H
#define RECTANGULARVOLUME_H


#include <iostream>
#include "Dimension3D.h"
#include "Vector3D.h"

using namespace std;

namespace XOR {

/**
 * Encapsulates the volume of an object. Contains information about radii 
 * in three directions and the front bottom left corner of an object
 * the main purpose of this object is collision detection, and is meant to be contained 
 * by a rectangularprism if painting is required. RectangularVolume is not a Renderable.
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
	RectangularVolume(Vector3D * point, Dimension3D * size);


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
	RectangularVolume(Vector3D * corner, float radius);


	/**
	 * Tests if the given point is contained (intersected) by the 
	 * rectangular volume object
	 */
	bool contains(Vector3D * point);


	/**
	 * Checks for containment within a specified plane.
	 * The idea is that this is faster than checking all planes
	 * each time
	 */
	bool contains(Vector3D * point, int plane);
	

	/**
	 * Generates a set of points that uniquely define the given volume
	 */
	void generatePoints(Vector3D * points[8]);


	Dimension3D * getDimension();

	//--getters for diameters--//
	float getXDiameter();
	float getYDiameter();
	float getZDiameter();

	Vector3D * getOrigin();


private:

	Dimension3D * _radii;
	Vector3D	* _origin;

};

}

#endif			// RECTANGULARVOLUME_H


#ifndef CYLINDRICALVOLUME_H
#define CYLINDRICALVOLUME_H


#include "../paint/Paint.h"
#include "../object3D/Point3D.h"
#include "../geometry/Dimension3D.h"


namespace XOR {

/**
 * This is used to represent a 3D cylinder.
 * For speed reasons, DON'T use this for collision detection. The 
 * rectangular volume is much better
 */
class CylindricalVolume
{

public:

	CylindricalVolume(Point3D *frontBottomLeft, float width, float height, float depth);
	CylindricalVolume(Point3D *frontBottomLeft, Dimension3D * dimension);
	
};

}

#endif			// CYLINDRICALVOLUME_H


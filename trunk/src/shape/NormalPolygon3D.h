#ifndef NORMALPOLYGON3D_H
#define NORMALPOLYGON3D_H


#include "../util/GraphicsConversionUtility.h"
#include "../paint/Paint.h"
#include "../geometry/Vector3D.h"
#include "Object3D.h"


namespace XOR {


/**
 *
 */
class NormalPolygon3D : public Object3D
{

public:


	/**
	 * Create it with the number of sides, centered around the given point. The
	 * NormalPolygon3D will always be created along the line z=0. Since
	 * NormalPolygon3D is an Object3D, transforms can be applied to position
	 * it.
	 */
	NormalPolygon3D(Vector3D * center, int numSides);


	/**
	 * Draws the NormalPolygon3D.
	 */
	void render();


	/**
	 * Set the paint to be used on the curren object.
	 */
	void setPaint(Paint * paint);
	
	
	/**
	 * is this needed?
	 */
	void resetNumSides(int);


protected:

	void calculateSides(void);

	void updatePaint(void);

	NormalPolygon3D();

};

}

#endif			// NORMALPOLYGON3D_H


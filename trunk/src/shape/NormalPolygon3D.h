#ifndef NORMALPOLYGON3D_H
#define NORMALPOLYGON3D_H


#include "../util/GraphicsConversionUtility.h"
#include "../paint/Paint.h"
#include "../geometry/Vector3D.h"
#include "Object3D.h"
#include <vector>
#include <math.h>

namespace XOR {


/**
 * An n-sided polygon.
 *
 * @author John Magnotti, Everette Clemmer
 * @version 1.0
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
	NormalPolygon3D(Vector3D * center, float radius, int numSides);


	/**
	 * Draws the NormalPolygon3D.
	 */
	void renderObject();


	/**
	 * Set the paint to be used on the curren object.
	 */
	void setPaint(Paint * paint);	

	/**
	 * Returns the center point of the NormalPolygon3D.
	 */
	Vector3D * getBaseVector();

	/**
	 * returns the bounding box for this polygon
	 */
	Dimension3D * getDimension();


private:

	NormalPolygon3D();

    vector<Vector3D*>  _vertices;

    Vector3D *          _center;
    Paint *             _paint;

    int                 _sides;
    float               _radius;

};

}

#endif			// NORMALPOLYGON3D_H


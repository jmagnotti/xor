#ifndef QUADRILATERAL3D_H
#define QUADRILATERAL3D_H

#include <math.h>
#include <string.h>

#include "../geometry/Vector3D.h"
#include "../geometry/Dimension3D.h"
#include "../util/PointScale.h"
#include "../paint/Paint.h"
#include "Object3D.h"


namespace XOR {

/**
 * Represents a quad in three dimensional space.
 * Considering a massive overhaul: Instead of specifying 4 points, have them
 * specify two points, then a dimension3D object (or 3 floats). Also, should be
 * able to calculate center. The new specification will allow for auto-sizing
 * of textures.
 */
class Quadrilateral3D : public Object3D
{

public:

	/** * Explicit Constructor
	 *
	 * Set each of the corners explicitly. The Quad will use a WHITE paint.
	 */
	Quadrilateral3D(Vector3D * p0, Vector3D * p1, Vector3D * p2, Vector3D * p3);
	Quadrilateral3D(Vector3D * p0, Vector3D * p1, Vector3D * p2, Vector3D * p3, PointScale * scale);

    
    /**
	 * Explicit Constructor
	 *
	 * Set each of the corners explicitly.
	 */
	Quadrilateral3D(Vector3D * p0, Vector3D * p1, Vector3D * p2, Vector3D * p3, Paint * paint);
	Quadrilateral3D(Vector3D * p0, Vector3D * p1, Vector3D * p2, Vector3D * p3, Paint * paint, PointScale * scale);
    


	/**
	 * Explicit Constructor
	 * This constructor is to be used only by the XML-to-GOR Tool. 
	 * Use the other constructors for other uses, as they are MUCH more efficeint
	 */
//	static Quadrilateral3D * CreateQuadrilateral3D(String, String, String, String, String);


    /**
     * Returns the normal associated with this object
     */
	Vector3D * getNormal() const;

    
    /**
     * Returns the dimension associated with this object
     */
    Dimension3D * getDimension();


	/**
	 * Returns the front bottom left corner
	 */
	Vector3D * getBaseVector();


	/**
	 * Sets a vertex of the quad.
	 * This could be used to do interesting transformations
	 */
	void setVertex(int vertexNumber, Vector3D * newVertex);


	/**
	 * Set the paint object for the quadrialteral
	 */
	void setPaint(Paint * paint);


	/**
	 * This flips the sign of the X and Z 
	 */
	void setNormal(Vector3D * normal);


	/**
	 * Print information about this quad
	 */
    void print();


    /**
     * Calls render on each point that comprises the quad3d
     */
	void renderObject(void);


protected:

	/**
	 * Calculates the center of the quadrilateral.
	 * The result is stored in _center.
	 * This is virtual so special case Quads (maybe an equilateral one?) can be optimized.
	virtual void calculateCenter();
	 */


	/**
     * Calculates the length and width of the quadrilateral.
	 * The results are stored in _dimension;
	 * This is virtual so special case Quads (maybe an equilateral one?) can be optimized.
	virtual void calculateDimension();
	 */

    virtual void buildWeights(PointScale * scale);


private:


	Quadrilateral3D();

	Dimension3D *	_dimension;
	Vector3D *		_center; 
	Vector3D *		_normal;

	Paint *		_paint;
	Vector3D *	_vertices[4];
	Vector3D *	_vertexWeights[4];

};

}

#endif		// QUADRILATERAL3D_H


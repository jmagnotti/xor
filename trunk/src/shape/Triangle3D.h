#ifndef QUADRILATERAL3D_H
#define QUADRILATERAL3D_H

#include <math.h>
#include <string.h>

#include "../geometry/Dimension3D.h"
#include "Object3D.h"
#include "../paint/Paint.h"


namespace XOR {


/**
 * Represents a triangle in three dimensional space.
 * Considering a massive overhaul: Instead of specifying 4 points, have them specify
 * two points, then a dimension3D object (or 3 floats). Also, should be able to calculate center. The new 
 * specification will allow for auto-sizing of textures.
 */
class Triangle3D : public Object3D
{

public:

	/**
	 * Explicit Constructor
	 *
	 * Set each of the corners explicitly. Does not set a paint value for the points
	 * Assumes that the points are already set to the correct colors
	 */
	Triangle3D(Vector3D * p0, Vector3D * p1, Vector3D * p2);

    
    /**
	 * Explicit Constructor
	 * Set each of the corners explicitly.
	 */
	Triangle3D(Vector3D * p0, Vector3D * p1, Vector3D * p2, Paint * paint);


	/**
	 * Explicit Constructor
	 * This constructor is to be used only by the XML-to-GOR Tool. 
	 * Use the other constructors for other uses, as they are MUCH more efficeint
	 */
//	static Triangle3D * CreateTriangle3D(String, String, String, String, String);


    /**
     * Returns the normal associated with this object
     */
	Vector3D * getNormal();

    
    /**
     * Returns the dimension associated with this object
     */
    Vector3D * getOrigin() const;
    Dimension3D * getDimension() const;


	/**
	 * Sets a vertex of the triangle.
	 * This could be used to do interesting transformations
	 */
	void setVertex(int vertexNumber, Vector3D * newVertex);


	/**
	 * Set the paint object for the triangle
	 */
	void setPaint(Paint * paint);


	/**
	 */
	virtual void setNormal(Vector3D * norm);


    /**
     * Calls render on each point that comprises the triangle
     */
	void draw(void);


	/**
	 * Returns a string representation of the triangle
	 */
    char * toString();


private:

	Triangle3D();

	Dimension3D *	_dimension;
	Paint	*		_paint;
	Vector3D *		_normal;
	Vector3D *		_vertices[3];

};

}

#endif		// QUADRILATERAL3D_H


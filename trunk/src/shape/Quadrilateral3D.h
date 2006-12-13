#ifndef QUADRILATERAL3D_H
#define QUADRILATERAL3D_H

#include <math.h>
#include <string.h>

#include "../geometry/Dimension3D.h"
#include "../util/GraphicsConversionUtility.h"
#include "../paint/Color.h"
#include "../paint/Paint.h"
#include "Point3D.h"


namespace XOR {


/**
 * Represents a quad in three dimensional space.
 * Considering a massive overhaul: Instead of specifying 4 points, have them specify
 * two points, then a dimension3D object (or 3 floats). Also, should be able to calculate center. The new 
 * specification will allow for auto-sizing of textures.
 */
class Quadrilateral3D : public Renderable
{

public:


	/**
	 *	Default Constructor. Creates a quad (0,0 : 1,1)
	 */
	Quadrilateral3D();


	/**
	 * Explicit Constructor
	 *
	 * Set each of the corners explicitly. Does not set a paint value for the points
	 * Assumes that the points are already set to the correct colors
	 */
	Quadrilateral3D(Point3D * p0, Point3D * p1, Point3D * p2, Point3D * p3);

    
    /**
	 * Explicit Constructor
	 *
	 * Set each of the corners explicitly.
	 */
	Quadrilateral3D(Point3D * p0, Point3D * p1, Point3D * p2, Point3D * p3, Paint *p);


	/**
	 * Explicit Constructor
	 * This constructor is to be used only by the XML-to-GOR Tool. 
	 * Use the other constructors for other uses, as they are MUCH more efficeint
	 */
//	static Quadrilateral3D * CreateQuadrilateral3D(String, String, String, String, String);


    /**
     * Returns the normal associated with this object
     */
	Point3D * getNormal();

    
    /**
     * Returns the dimension associated with this object
     */
    Dimension3D * getSize();


	/**
	 * Sets a vertex of the quad.
	 * This could be used to do interesting transformations
	 */
	void setVertex(int vertexNumber, Point3D * newVertex);


	/**
	 * Sets the color of a particular vertex
	 * Pass in the point to set and its color
	 */
	void setAllColors(Paint * p);


	/**
	 * Set the paint object for the quadrialteral
	 */
	void setPaint(Paint * p);


	/**
	 * This flips the sign of the X and Z 
	 * This is virtual so special case Quads (maybe an equilateral one?) can be optimized.
	 */
	virtual void setNormal(Point3D * norm);


    /**
     * Calls render on each point that comprises the quad3d
     */
	void render(void);


protected:

	/**
	 * Calculates the center of the quadrilateral.
	 * The result is stored in _center.
	 * This is virtual so special case Quads (maybe an equilateral one?) can be optimized.
	 */
	virtual void calculateCenter();


	/**
     * Calculates the length and width of the quadrilateral.
	 * The results are stored in _dimension;
	 * This is virtual so special case Quads (maybe an equilateral one?) can be optimized.
	 */
	virtual void calculateDimension();


	Dimension3D *	_dimension;
	Paint	*		_paint;
	Point3D *		_center; 
	Point3D *		_normal;
	Point3D *		_vertices[4];

};

}

#endif		// QUADRILATERAL3D_H

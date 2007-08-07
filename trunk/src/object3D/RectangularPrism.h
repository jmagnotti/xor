#ifndef RECTANGULARPRISM_H
#define RECTANGULARPRISM_H


#include <vector>

#include "../util/GraphicsConversionUtility.h"
#include "../util/PointScale.h"
#include "../paint/Paint.h"
#include "Object3D.h"
#include "Quadrilateral3D.h"
#include "../geometry/RectangularVolume.h"


namespace XOR {

/**
 * A three-dimensional object with six quadrilateral sides. Should be six
 * Rectangular sides. #FIXME
 *
 */
class RectangularPrism : public Object3D
{

public:

	/**
	 * Face constants.
	 */
	static const int TOP;
	static const int BOTTOM;
	static const int RIGHT;
	static const int LEFT;
	static const int FRONT;
	static const int REAR;


	/**
	 * Full control of specs
	 */
	RectangularPrism(Vector3D * point, float sizeX, float sizeY, float sizeZ,
			Paint * paint);

    /**
     * Explicit constructor
     */
	RectangularPrism(Vector3D * point, Dimension3D * size, Paint * paint);


	/**
	 * Explicit Constructor
	 */
	RectangularPrism(RectangularVolume * rv);


	/** 
	 * Calculates the normals for the given object
	 */
	virtual void calculateNormals(void);


	/**
	 * returns if the point is within the rect prism
	 */
	virtual bool checkCollision(Vector3D * position);


	/** 
	 * Returns the registration point of the rect prism
	Vector3D * getBaseVector() const;
	 */


	/**
	 * Returns the dimension for the object
	Dimension3D * getDimension() const;
	 */


	/**
	 * Removes a face from the cube. Ex. Remove BOTTOM so that the Cube floor and the terrain
	 * do not overlap.
	 */
	Quadrilateral3D * removeFace(const int faceToRemove);


    /**
     * Set the order in which the quads are being rendered. This is useful if
     * depth testing is disabled. This could also be used to implement culling
     * by padding the array with -1.
     */
    void setRenderingOrder(int order[6]);


	/**
	 * This is a high level render command. Most of the actual work will
	 * be delegated to the Quadrilateral3D object.
	 */
	void renderObject();


	/**
	 * Set the paint attributes
	 */
	void setPaint(Paint * p);


    /**
     * Prints information about the prism
     */
    void printInfo();


    /**
     * Returns the size of the prism
     */
	virtual Dimension3D * getDimension();


    /**
     * Returns the registration point of the prism
     */
	virtual Vector3D * getBaseVector();	


protected:

	/**
	 * Puts the created quads into the vector. This is done in a seperate
	 * method in case we want to return to a default RectPrism.
	 * NOTE: occluded faces will be reset here
	 */
	void setFaces(void);
	
	
	/**
	 * Calls on the underlying RectangularVolume object to generate the quads
	 * of the prism
	 */
	void setup(void);


	/**
	 * updates the paint of the faces by giving them new colored points
	void updatePaint(void);
	 */


protected:

	RectangularPrism();
	
    int                 _order[6];
	Paint *				_paint;
	Vector3D *			_points[8];
	Vector3D *			_normals[6];
	RectangularVolume *	_volume;
	
	vector<Quadrilateral3D*> _faces;

};

}

#endif			// RECTANGULARPRISM_H


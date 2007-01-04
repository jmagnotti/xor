#ifndef RECTANGULARPRISM_H
#define RECTANGULARPRISM_H


#include <vector>

#include "../util/GraphicsConversionUtility.h"
#include "../paint/Paint.h"
#include "Quadrilateral3D.h"
#include "../geometry/RectangularVolume.h"
#include "../transform/Positionable.h"


namespace XOR {


/**
 * A three-dimensional object with six quadrilateral sides.
 */
class RectangularPrism : public Renderable, public Positionable
{

public:

	const static int FRONT	= 0;
	const static int REAR	= 1;
	const static int RIGHT	= 2;
	const static int LEFT	= 3;
	const static int TOP	= 4;
	const static int BOTTOM	= 5;


	/**
	 * Default Constructor
	 */
	RectangularPrism();


	/**
	 * Full control of specs
	 */
	RectangularPrism(Point3D * point, float sizeX, float sizeY, float sizeZ, Paint * p);


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
	bool checkCollision(Point3D * position);


	/** 
	 * Returns the registration point of the rect prism
	 */
	virtual Point3D * getRegistrationPoint();


	/**
	 * This is a high level rendering command. Most of the actual work will
	 * be delegated to the Quadrilateral3D object (which in turn delegates to Point3D).
	 */
	void render(void);


	/**
	 * Removes a face from the cube. Ex. Remove BOTTOM so that the Cube floor and the terrain
	 * do not overlap.
	 */
	void removeFace(int faceToRemove);


	/**
	 * Set the _paint attributes
	 */
	void setPaint(Paint * p);


    /**
     *
     */
    void printInfo();

protected:
	
	Paint *				_paint;
	Point3D *			_points[8];			//storing the key points makes things faster
	Point3D *			_normals[6];
	RectangularVolume *	_volume;
	
	
	/**
	 * We need an ordered collection, so a vector is used
	 */
	vector<Quadrilateral3D*>	_faces;


	/**
	 * Puts the created quads into the vector. This is done in a seperate in case we want 
	 * to return to a default RectPrism.
	 * NOTE: occluded faces will be reset here
	 */
	void setFaces(void);
	
	
	/**
	 * Calls on the underlying RectangularVolume object to generate the quads of the prism
	 */
	void setup(void);



	/**
	 * updates the paint of the faces by giving them new colored points
	 */
	void updatePaint(void);

};

}

#endif			// RECTANGULARPRISM_H


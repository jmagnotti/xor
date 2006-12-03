#ifndef NORMALPOLYGON3D_H
#define NORMALPOLYGON3D_H


#include "../util/GraphicsConversionUtility.h"
#include "../paint/Paint.h"
#include "Point3D.h"
#include "Renderable.h"

namespace XOR {


class NormalPolygon3D : public Renderable
{

public:


	/**
	 * Default Constructor
	 */
	NormalPolygon3D();


	/**
	 * Create it with the number of sides
	 */
	NormalPolygon3D(int);


	/**
	 * Calls render on the underlying renderer
	 */
	void render(void);


	/**
	 * Should do tricky stuff if the paint is a gradient or texture
	 */
	void setPaint(Paint*);
	
	
	/**
	 * is this needed?
	 */
	void resetNumSides(int);


protected:

	bool		compiled;
	
	void recalculateSides(void);


	void updatePaint(void);


};

}

#endif			// NORMALPOLYGON3D_H


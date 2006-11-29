#ifndef ARC3D_H
#define ARC3D_H

#include <string>

#include "../util/GraphicsConversionUtility.h"
#include "Renderable.h"
#include "../paint/Paint.h"
#include "Point3D.h"


namespace XOR {


/**
 * Collection of points that draws an arc. This is NOT a circle class. There is a circle class,
 * and it uses a structure more similar to NormalPolygon3D instead of Arc3D
 */
class Arc3D : public Renderable
{

public:

	/**
	 * Center, radius, degrees of coverage, number of sections CCW
	 */
    Arc3D(Point3D * cen, float rad, int deg, int res);


	/**
	 * Explicit Constructor
	 * This constructor is to be used only by the XML-to-GOR Tool. 
	 * Use the other constructors for other uses, as they are MUCH more efficeint
	 */
//	static Arc3D * CreateArc3D(String, String, String, String, String, String);


	/**
	 * Renders the points
	 */
	void render(void);


	/**
	 * This should be smart enough to calculate 
	 * gradients between sections accurately
	 */
	void setPaint(Paint*);


protected:

    float		radius;
	int			degrees, resolution;

	Paint   *	paint;

	Point3D *	center;
	Point3D *	points;	//array of points 


	/**
	 * Calculates the colors of each of the points
	 */
	void updatePaint(void);

};

}

#endif          //ARC3D_H

#include "Arc3D.h"

namespace XOR {

/**
 * Creates an arc with radius rad and center cen
 */
Arc3D::Arc3D(Point3D *cen, float rad, int deg, int res)
{
    radius = rad;
    center = cen;

	degrees = deg;
	resolution = res;
}


/**
 * Renders the arc
 */
void Arc3D::render(void)
{
	cout << "Arc3D render not implemented" << endl;
}


/**
 * Sets the paint of the arc
 */
void Arc3D::setPaint(Paint *p)
{
//	paint = p;
//	updatePaint();
}


/**
 * Sets the color values of the points based on the Paint object
 */
void Arc3D::updatePaint()
{
//	int gradient = paint->getGradient();
}

}


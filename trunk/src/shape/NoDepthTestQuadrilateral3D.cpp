#include "NoDepthTestQuadrilateral3D.h"


namespace XOR {

/*
 * pass off to parent
 */
NoDepthTestQuadrilateral3D::NoDepthTestQuadrilateral3D(Vector3D * p0,
		Vector3D * p1, Vector3D * p2, Vector3D * p3)
: Quadrilateral3D(p0, p1, p2, p3)
{}

/*
 * pass off to parent
*/
NoDepthTestQuadrilateral3D::NoDepthTestQuadrilateral3D(Vector3D * p0, Vector3D
        * p1, Vector3D * p2, Vector3D * p3, Paint * paint) 
: Quadrilateral3D(p0, p1, p2, p3, paint)
{}


/*
 * pass off to parent
 */
NoDepthTestQuadrilateral3D::NoDepthTestQuadrilateral3D(Vector3D * p0, 
        Vector3D * p1, Vector3D * p2, Vector3D * p3, Paint * paint, 
        PointScale * colorScale, TextureScale * textureScale) 
: Quadrilateral3D(p0, p1, p2, p3, paint, colorScale, textureScale)
{}


/*
 * disable, render, enable
 */
void NoDepthTestQuadrilateral3D::render()
{
	glPushAttrib(GL_DEPTH_TEST);
	glDisable(GL_DEPTH_TEST);

	push();
		renderObject();
	pop();

	glPopAttrib();
}

}

	

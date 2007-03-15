#ifndef NODEPTHTESTQUADRILATERAL3D_H
#define NODEPTHTESTQUADRILATERAL3D_H


#include "../../include/SDL_opengl.h"

#include "Quadrilateral3D.h"

#include "../geometry/Vector3D.h"
#include "../paint/Paint.h"
#include "../util/PointScale.h"


namespace XOR {

/**
 * A quad that disables depth testing before it renders.
 *
 * @author John Magnotti
 * @author Michael Lam
 * @version 1.0
 */
class NoDepthTestQuadrilateral3D : public Quadrilateral3D
{

public:

	/** 
	 * Explicit Constructor
	 *
	 * Set each of the corners explicitly. The Quad will use a WHITE paint.
	 */
	NoDepthTestQuadrilateral3D(Vector3D * p0, Vector3D * p1, Vector3D *
			p2, Vector3D * p3);

	NoDepthTestQuadrilateral3D(Vector3D * p0, Vector3D * p1, Vector3D *
			p2, Vector3D * p3, PointScale * scale);

    
    /**
	 * Explicit Constructor
	 *
	 * Set each of the corners explicitly.
	 */
	NoDepthTestQuadrilateral3D(Vector3D * p0, Vector3D * p1, Vector3D *
			p2, Vector3D * p3, Paint * paint);

	NoDepthTestQuadrilateral3D(Vector3D * p0, Vector3D * p1, Vector3D *
			p2, Vector3D * p3, Paint * paint, PointScale * scale);
    

    /**
     * Disables depth testing, renders, then renables depth testing (if
	 * it was enabled before).
     */
	void render(void);


private:

	NoDepthTestQuadrilateral3D();

	Quadrilateral3D * _quad;

};

}

#endif		// NODEPTHTESTQUADRILATERAL3D_H


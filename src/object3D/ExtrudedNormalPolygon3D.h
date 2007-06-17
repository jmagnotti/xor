#ifndef EXTRUDEDNORMALPOLYGON3D_H
#define EXTRUDEDNORMALPOLYGON3D_H


#include <vector>

#include "NormalPolygon3D.h"
#include "Object3D.h"
#include "../geometry/Vector3D.h"


using namespace std;

namespace XOR {

/**
 * Creates 3D solids from NormalPolygon3D objects.
 *
 * @author John Magnotti
 * @version 1.0
 */
class ExtrudedNormalPolygon3D : public Object3D
{

public:

    /**
     * Extrude the given shape along the Z-Axis. The memory associated with the
     * shape object is aliased, so tthe caller should not attempt to reclaim
     * it. Upon destruction, the memory associate with the NormalPolygon3D will
     * also be reclaimed. This also means that you should not extrude the same
     * NormalPolygon3D multiple times. 
     */
    ExtrudedNormalPolygon3D(NormalPolygon3D * shape, int depth);


    /**
     * Same as the above constructor, but does not alias any parts of the shape
     * class. This allows for the caller to reuse the shape after it has been
     * extruded. Consequently, the calling class is responsible for freeing
     * memory associated with the NormalPolygon3D.
     */
    ExtrudedNormalPolygon3D(NormalPolygon3D * shape, int depth, bool clone);


    /**
     * Renders the object as a series of quad strips.
     */
    void renderObject();

    Vector3D * getBaseVector();
    Dimension3D * getDimension();


private:

    /**
     * Private constructor
     */
    ExtrudedNormalPolygon3D();


    /**
     * construction with aliasing of shape's point vector
     */
    void buildWithAlias(NormalPolygon3D * shape, int depth);
   

    /**
     * construction without aliasing of shape's point vector
     */
    void buildWithoutAlias(NormalPolygon3D * shape, int depth);


    NormalPolygon3D * _shape;
    int               _depth;
    vector<Vector3D*> _vertices;

};

}

#endif			// EXTRUDEDNORMALPOLYGON3D_H


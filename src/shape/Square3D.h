#ifndef SQUARE3D_H
#define SQUARE3D_H


#include "Point3D.h"
#include "Quadrilateral3D.h"
#include "../paint/Paint.h"

namespace XOR {

/**
 * Doesn't really do 3D very well. Just does X,Y squares at the moment.
 * If we end up refactoring Quad3D as planned, then we can changed this as well.
 */
class Square3D : public Quadrilateral3D
{
public:

	Square3D();


    /**
     * point : bottom left corner
     * diameter : x & y 
     * paint : paint object to use
     *
     * x, y+d,z     x,  y+d,z
     * x, y,  z     x+d,y,  z 
     *
     *
     */
	Square3D(Point3D * point, float diameter, Paint * paint);

};

}

#endif			// SQUARE3D_H


#ifndef SQUARE3D_H
#define SQUARE3D_H


#include "Point3D.h"
#include "Quadrilateral3D.h"
#include "../paint/Paint.h"

namespace XOR {

/**
 * Convenience class for creating squares. Doesn't really do 3D very well. Just
 * does X,Y squares at the moment. If we end up refactoring Quad3D as planned,
 * then we can changed this as well.
 *
 * @author John Magnotti, Michael Lam
 * @version 1.0
 */
class Square3D : public Quadrilateral3D
{
public:

    /**
     *
     */
	Square3D();


    /**
     *
     */
	Square3D(Point3D * point, float diameter, Paint * paint);

};

}

#endif			// SQUARE3D_H


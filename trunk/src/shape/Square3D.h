#ifndef SQUARE3D_H
#define SQUARE3D_H


#include "Point3D.h"
#include "Quadrilateral3D.h"
#include "../paint/Paint.h"

namespace XOR {


class Square3D : public Quadrilateral3D
{
public:

	Square3D();

	Square3D(Point3D * point, float diameter, Paint * paint);

};

}

#endif			// SQUARE3D_H


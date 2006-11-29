#include "AdornableCube.h"

namespace XOR {

AdornableCube::AdornableCube()
{
    Cube::Cube();
}


AdornableCube::AdornableCube(Point3D* point, float rad, Paint *p)
{
    Cube::Cube(point, rad, p);
}


/*
 * Delegates rendering to the parent prism
 */
void AdornableCube::render()
{
    AdornablePrism::render();
}

}


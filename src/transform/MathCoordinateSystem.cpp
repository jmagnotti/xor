#include "MathCoordinateSystem.h"


namespace XOR {

MathCoordinateSystem * MathCoordinateSystem::_mathCoordinateSystem =
    NULL;

/*
 * Protected constructor
 */
MathCoordinateSystem::MathCoordinateSystem()
{
    for (int i=0; i<3; i++)
        _rotations[i] = new Rotate();
}


/*
 * Singleton accessor
 */
CoordinateSystem * MathCoordinateSystem::GetInstance()
{
    if (_mathCoordinateSystem == NULL)
        _mathCoordinateSystem = new MathCoordinateSystem();

    return _mathCoordinateSystem;
}

}


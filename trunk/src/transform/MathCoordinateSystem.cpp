#include "MathCoordinateSystem.h"


namespace XOR {

MathCoordinateSystem * MathCoordinateSystem::_mathCoordinateSystem =
    NULL;

/*
 * Protected constructor
 */
MathCoordinateSystem::MathCoordinateSystem()
{
    _xRotation = new Rotate();
    _yRotation = new Rotate();
    _zRotation = new Rotate();
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

